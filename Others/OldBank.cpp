#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

struct BankData
{
    std::string accName;
    int accPass;
    std::string accCurreny;
    long long int accBalance;
};

void clearError()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void continutionRequest(bool &inBank)
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

int askChoice(std::vector<int> validOptions)
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

void saveAccount(std::string &fileName, std::vector<BankData> &Bank)
{
    std::ofstream ofile(fileName);
    for (const auto &tempBank : Bank)
    {
        ofile
            << tempBank.accName << " "
            << tempBank.accPass << " "
            << tempBank.accCurreny << " "
            << tempBank.accBalance << "\n";
    }
}

void accountCreation(std::vector<BankData> &Bank)
{
    std::cout << "Nice! please enter the details \n";

    BankData newAccount;

    while (true)
    {
        std::cout << "Account name: ";
        std::cin >> newAccount.accName;
        bool accFound = false;
        for (size_t i{0}; i < Bank.size(); i++)
        {
            if (newAccount.accName == Bank[i].accName)
            {
                accFound = true;
                break;
            }
        }
        if (accFound)
        {
            std::cout << "An account with this Name already exits \n";
            std::cout << "Try with new name";
        }
        break;
    }

    while (true)
    {
        std::cout << "Account currency (inr / usd):";
        std::cin >> newAccount.accCurreny;

        if (newAccount.accCurreny != "inr" &&
            newAccount.accCurreny != "usd" &&
            newAccount.accCurreny != "INR" &&
            newAccount.accCurreny != "USD")
        {
            std::cout << "This currency is unrecognised! \n";
            std::cout << "Recognised currecny inr / usd \n";
            clearError();
            continue;
        }
        break;
    }

    bool verifyingPass = true;
    while (verifyingPass)
    {

        std::cout << "Account pass: ";
        std::cin >> newAccount.accPass;

        while (true)
        {
            int passVerification;
            std::cout << "Verify the pass: ";
            std::cin >> passVerification;

            if (passVerification == newAccount.accPass)
            {
                std::cout << "Your pass has been verified \n";
                std::cout << std::endl;
                verifyingPass = false;
                break;
            }
            else
            {
                std::cout << "You failed pass reverfication \n";

                std::cout << "1. Retry pass verification \n";
                std::cout << "2. Try with new pass \n";

                int passVerficationChoice = askChoice({1, 2});

                if (passVerficationChoice == 1)
                {
                    continue;
                }
                else if (passVerficationChoice == 2)
                {
                    break;
                }
            }
        }
    }
    std::cout << "Got money to diposit?\n";
    std::cout << "1. Yes \n";
    std::cout << "2. No \n";
    int depositChoice = askChoice({1, 2});
    if (depositChoice == 1)
    {
        std::cout << "Enter Amout to Deposit: ";
        std::cin >> newAccount.accBalance;
        std::cout << "Congratulations You account has been created! \n";
    }
    else if (depositChoice == 2)
    {
        newAccount.accBalance = 0;
    }
    Bank.push_back(newAccount);
}
void bankEmpty(std::vector<BankData> &Bank, std::string &fileName, bool &inBank)
{
    std::cout << "We have no accounts, consider creating one! \n";
    std::cout << "1. Create account \n";
    std::cout << "2. Leave Bank \n";
    int userChoice1 = askChoice({1, 2});

    if (userChoice1 == 1)
    {
        accountCreation(Bank);
        saveAccount(fileName, Bank);
        continutionRequest(inBank);
    }
    else if (userChoice1 == 2)
    {
        inBank = false;
    }
}
void accountDeletion(std::vector<BankData> &Bank, std::string fileName, bool &inBank)
{
    if (Bank.empty())
    {
        bankEmpty(Bank, fileName, inBank);
    }
    else
    {
        std::cout << "Choose what account to delete: \n";
        std::vector<int> temp;
        for (size_t i{0}; i < Bank.size(); i++)
        {
            temp.push_back(i + 1);
            std::cout
                << i + 1 << ". " << Bank[i].accName
                << " " << Bank[i].accCurreny << "\n";
        }
        int accDeletionChoice = askChoice(temp);

        int providedPass;
        std::cout << "Enter pass to delete account: ";
        std::cin >> providedPass;

        if (providedPass == Bank[accDeletionChoice - 1].accPass)
        {
            Bank.erase(Bank.begin() + (accDeletionChoice - 1));
            std::cout << "Account have been sucessfully deleted! \n";
        }
        else
        {
            std::cout << "You entered wrong pass, cant delete the account \n";
            continutionRequest(inBank);
        }
    }
}

void depositMoney(std::vector<BankData> &Bank, std::string fileName, bool &inBank)
{
    if (Bank.empty())
    {
        bankEmpty(Bank, fileName, inBank);
    }
    else
    {
        std::cout << "Select what account to deposit: \n";
        std::vector<int> temp;
        for (size_t i{0}; i < Bank.size(); i++)
        {
            temp.push_back(i + 1);
            std::cout
                << i + 1 << ". " << Bank[i].accName
                << " " << Bank[i].accCurreny << "\n";
        }
        int accDepositChoice = askChoice(temp);

        long long int despositMoney;

        std::cout << "Enter amount to deposit: ";
        std::cin >> despositMoney;

        Bank[accDepositChoice - 1].accBalance += despositMoney;
    }
}
void withdrawMoney(std::vector<BankData> &Bank, std::string fileName, bool &inBank)
{
    if (Bank.empty())
    {
        bankEmpty(Bank, fileName, inBank);
    }
    std::cout << "Select what account to withdraw: \n";
    std::vector<int> temp;
    for (size_t i{0}; i < Bank.size(); i++)
    {
        temp.push_back(i + 1);
        std::cout
            << i + 1 << ". " << Bank[i].accName
            << " " << Bank[i].accCurreny << "\n";
    }
    int accWithdrawtChoice = askChoice(temp);

    int withdrawPass;
    std::cout << "Enter pass to withdraw money: ";
    std::cin >> withdrawPass;

    if (withdrawPass == Bank[accWithdrawtChoice - 1].accPass)
    {

        while (true)
        {
            std::cout << "Enter amount to withdraw: ";
            long long int withdrawMoney;
            std::cin >> withdrawMoney;

            if (withdrawMoney > Bank[accWithdrawtChoice - 1].accBalance)
            {
                std::cout << "You have less balance than you are withdrawing! \n";
                std::cout << "Your Balance: " << Bank[accWithdrawtChoice - 1].accBalance << "\n";
                std::cout << "Please try again \n";
            }
            else
            {
                Bank[accWithdrawtChoice - 1].accBalance -= withdrawMoney;
                break;
            }
        }
    }
    else
    {
        std::cout << "You entered wrong pass! \n";
    }
}

void showBalance(std::vector<BankData> &Bank, std::string fileName, bool &inBank)
{
    if (Bank.empty())
    {
        bankEmpty(Bank, fileName, inBank);
    }
    std::cout << "Select account to check balance: \n";

    std::vector<int> temp;
    for (size_t i{0}; i < Bank.size(); i++)
    {
        temp.push_back(i + 1);
        std::cout
            << i + 1 << ". " << Bank[i].accName
            << " " << Bank[i].accCurreny << "\n";
    }
    int accCheckBalancetChoice = askChoice(temp);

    std::cout << "Amount left in account "
              << Bank[accCheckBalancetChoice - 1].accName << " is "
              << Bank[accCheckBalancetChoice - 1].accBalance << " \n";
}

int main()
{
    std::string fileName = "BankData.txt";
    std::vector<BankData> Bank = loadData(fileName);

    bool inBank = true;

    while (inBank)
    {

        std::cout
            << "Welcome to bank of Chibu, What service do you need?"
            << std::endl;
        std::cout << "1. Account creation \n";
        std::cout << "2. Account deletion \n";
        std::cout << "3. Deposit in Account \n";
        std::cout << "4. Withdraw from account \n";
        std::cout << "5. Check balance in account \n";
        std::cout << "6. Leave Bank \n";

        int userChoice = askChoice({1, 2, 3, 4, 5, 6});

        if (userChoice == 1)
        {
            accountCreation(Bank);
            saveAccount(fileName, Bank);
            continutionRequest(inBank);
        }
        else if (userChoice == 2)
        {
            accountDeletion(Bank, fileName, inBank);
            saveAccount(fileName, Bank);
            continutionRequest(inBank);
        }
        else if (userChoice == 3)
        {
            depositMoney(Bank, fileName, inBank);
            saveAccount(fileName, Bank);
        }
        else if (userChoice == 4)
        {
            withdrawMoney(Bank, fileName, inBank);
            saveAccount(fileName, Bank);
            continutionRequest(inBank);
        }
        else if (userChoice == 5)
        {
            showBalance(Bank, fileName, inBank);
            continutionRequest(inBank);
        }
        else if (userChoice == 6)
        {
            inBank = false;
        }
    }
}