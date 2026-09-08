#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

struct BankData
{
    std::string accName;
    long long int accPass;
    std::string accCurreny;
    long long int accBalance;
};

void clearError();

void continuationRequest(bool &inBank);

int askChoice(const std::vector<int> &validOptions);

std::vector<BankData> loadData(const std::string &fileName);

std::string encodeName(const std::string& name);
std::string decodeName(const std::string& name);