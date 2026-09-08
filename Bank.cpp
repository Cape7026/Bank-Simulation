#include "Headers/Tools.hpp"
#include "Headers/AccountHandling.hpp"

int main()
{
    std::string fileName = "BankData.txt";
    std::vector<BankData> Bank = loadData(fileName);

    bool inBank = true;

    while (inBank)
    {
        std::cout
            << "\nWelcome to bank of Chibu, What service do you need?\n"
            << "1. Account creation \n"
            << "2. Account deletion \n"
            << "3. Deposit in Account \n"
            << "4. Withdraw from account \n"
            << "5. Check balance in account \n"
            << "6. Leave Bank \n";

        int userChoice = askChoice({1, 2, 3, 4, 5, 6});

        switch (userChoice)
        {
        case 1:
            accountCreation(Bank);
            break;
        case 2:
            accountDeletion(Bank);
            break;
        case 3:
            depositMoney(Bank);
            break;
        case 4:
            withdrawMoney(Bank);
            break;
        case 5:
            showBalance(Bank);
            break;
        case 6:
            inBank = false;
            break;
        }

        saveAccount(fileName, Bank);
        continuationRequest(inBank);
    }


}
