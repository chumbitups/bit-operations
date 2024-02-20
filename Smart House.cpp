#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>

enum switches
{
    LIGHTS_INSIDE = 1,
    LIGHTS_OUTSIDE = 2,
    HEATERS = 4,
    WATER_PIPE_HEATING = 8,
    CONDITIONER = 16
};

unsigned int switchesState = 0;
int tempIn = 0;
int tempOut = 0;
int lightTemp = 5000;
std::string movement = " ";
std::string light = " ";
std::string report = "";

bool is_On(int device)
{
    if ((switchesState & device) == device)
    {
        return true;
    }
    return false;
}

void check_Heaters()
{
    if (tempIn < 22 && (!is_On(HEATERS)))
    {
        switchesState |= HEATERS;
        report += "Heaters ON!\n";
    }
    else if (tempIn >= 25 && is_On(HEATERS))
    {
        switchesState &= ~HEATERS;
        report += "Heaters OFF!\n";
    }
}

void check_Conditioner()
{
    if (tempIn >= 30 && !is_On(CONDITIONER))
    {
        switchesState |= CONDITIONER;
        report += "Conditioner ON!\n";
    }
    else if (tempIn <= 25 && is_On(CONDITIONER))
    {
        switchesState &= ~CONDITIONER;
        report += "Conditioner OFF!\n";
    }
}

void check_Water_Pipe_Heating()
{
    if (tempOut < 0 && !is_On(WATER_PIPE_HEATING))
    {
        switchesState |= WATER_PIPE_HEATING;
        report += "Water pipe heating ON!\n";
    }
    else if (tempOut > 5 && is_On(WATER_PIPE_HEATING))
    {
        switchesState &= ~WATER_PIPE_HEATING;
        report += "Water pipe heating OFF!\n";
    }
}

void check_Lights_Inside(int time)
{
    if (light == "on" && !is_On(LIGHTS_INSIDE))
    {
        switchesState |= LIGHTS_INSIDE;
        if (((time % 24) > 16) && ((time % 24) < 20))
        {
            lightTemp -= 575;
        }
        report += "Lights inside ON!\n";
    }
    else if (light == "off" && is_On(LIGHTS_INSIDE))
    {
        switchesState &= ~LIGHTS_INSIDE;
        report += "Lights inside OFF!\n";
    }
}

void check_Lights_Outside(int time)
{
    if (movement == "yes" && (((time % 24) > 16) || ((time % 24) < 5)) && !is_On(LIGHTS_OUTSIDE))
    {
        switchesState |= LIGHTS_OUTSIDE;
        report += "Lights outside ON!\n";
    }
    else if (movement == "no" && is_On(LIGHTS_OUTSIDE))
    {
        switchesState &= ~LIGHTS_OUTSIDE;
        report += "Lights outside OFF!\n";
    }
}

int main()
{
    std::string answer = " ";
    for (int time = 0; time <= 48; time++)
    {
        std::cout << "Temperature inside, temperature outside, movement, lights: ";
        std::getline(std::cin, answer);
        std::stringstream indicators(answer);
        indicators >> tempIn >> tempOut >> movement >> light;

        check_Heaters();
        check_Conditioner();
        check_Water_Pipe_Heating();
        check_Lights_Inside(time);
        check_Lights_Outside(time);

        std::cout << report << std::endl
                  << "Color temperature = " << lightTemp << "K" << std::endl;
        report = "";
    }
}