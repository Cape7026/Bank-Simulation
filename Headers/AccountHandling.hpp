#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

#include "Tools.hpp"

void saveAccount(std::string &fileName, std::vector<BankData> &Bank);

void bankEmpty();

int chooseAccount(const std::vector<BankData> &Bank);

void accountCreation(std::vector<BankData> &Bank);

void accountDeletion(std::vector<BankData> &Bank);

void depositMoney(std::vector<BankData> &Bank);

void withdrawMoney(std::vector<BankData> &Bank);

void showBalance(std::vector<BankData> &Bank);
