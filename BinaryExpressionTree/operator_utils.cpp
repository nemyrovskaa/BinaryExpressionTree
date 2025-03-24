#include "operator_utils.h"

OperatorUtils::OperatorUtils()  // constructor of class Operator
{
    operators.insert(std::make_pair("(", OperatorData(0, -1, true, nullptr)));
    operators.insert(std::make_pair(")", OperatorData(0, -1, true, nullptr)));
    operators.insert(std::make_pair("+", OperatorData(1, 0, true,
        [](double& left, double& right) -> double { return left + right; })));

    operators.insert(std::make_pair("-", OperatorData(1, 1, true, 
        [](double& left, double& right) -> double { return left - right; })));

    operators.insert(std::make_pair("*", OperatorData(2, 2, true,
        [](double& left, double& right) -> double { return left * right; })));

    operators.insert(std::make_pair("/", OperatorData(2, 3, true,
        [](double& left, double& right) -> double { return left / right; })));

    operators.insert(std::make_pair("^", OperatorData(3, 4, false,
        [](double& left, double& right) -> double
        {
            if (((left == 0. || left == std::numeric_limits<double>::infinity()) && right == 0.) ||
                (left != 0 && right == std::numeric_limits<double>::infinity()))
                return std::numeric_limits<double>::quiet_NaN();
            return pow(left, right);
        })));
}

bool OperatorUtils::symbIsOperator(std::string& symb)
{
    if (operators.find(symb) == operators.end())
        return false;  // symb is not an operator
    return true;  // symb is an operator
}

int OperatorUtils::getPriority(std::string& symb)
{
    if (operators.find(symb) == operators.end())
        throw std::invalid_argument("NO operator found.");  // no operator found
    return operators.at(symb).priority;  // return priority of operator
}

int OperatorUtils::getIdentifier(std::string& symb)
{
    if (operators.find(symb) == operators.end())
        return -1;  // symb is a number
    return operators.at(symb).identifier;  // return identifier of operator
}

bool OperatorUtils::isAssociative(std::string& symb)
{
    if (operators.find(symb) == operators.end())
        throw std::invalid_argument("NO operator found.");  // no operator found
    return operators.at(symb).is_associative;  // return associativity of operator
}

std::string OperatorUtils::getSymb(int identifier)
{
    for (auto i : operators)
    {
        if (i.second.identifier == identifier)
            return i.first;  // return operator by identifier
    }
    return std::string();  // return empty string if operator not found
}

std::function<double(double&, double&)> OperatorUtils::getCalcFunc(std::string symb)
{
    if (operators.find(symb) == operators.end())
        throw std::invalid_argument("NO operator found.");  // no operator found
    return operators.at(symb).calculation_func;  // return function for passed operator
}