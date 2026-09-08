#include "Headers/Tools.hpp"
#include "Headers/AccountHandling.hpp"

void clearError()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void continuationRequest(bool &inBank)
{
    while (true)
    {
        std::cout << "Would you like to continue? (y/n): ";
        char continueOtpion;
        std::cin >> continueOtpion;

        if (continueOtpion == 'y')
        {
            break;
        }
        else if (continueOtpion == 'n')
        {
            inBank = false;
            break;
        }
        else
        {
            std::cout << "Excuse me? ";
        }
    }
}

int askChoice(const std::vector<int> &validOptions)
{
    int choice;
    while (true)
    {
        std::cout << "Choose an option: ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cout << "Enter a valid choice \n";
            clearError();
        }
        else
        {
            for (int i{0}; i < validOptions.size(); i++)
            {
                if (choice == validOptions[i])
                {
                    return choice;
                }
            }
        }
        std::cout << "Entered option didnt match \n";
    }
}
std::string encodeName(const std::string& name)
{
    std::string encoded = name;
    for (size_t i = 0; i < encoded.length(); i++)
    {
        if (encoded[i] == ' ')
            encoded[i] = '_';
    }
    return encoded;
}
std::string decodeName(const std::string& name)
{
    std::string decoded = name;
    for (size_t i = 0; i < decoded.length(); i++)
    {
        if (decoded[i] == '_')
            decoded[i] = ' ';
    }
    return decoded;
}

std::vector<BankData> loadData(const std::string &fileName)
{
    std::ifstream ifile(fileName);

    std::vector<BankData> Bank;
    if (!ifile.is_open())
    {
        std::ofstream ofile(fileName);
        return Bank;
    }
    BankData temp;
    while (ifile >> temp.accName >> temp.accPass >> temp.accCurreny >> temp.accBalance)
    {
        Bank.push_back(temp);
    }
    return Bank;
}
