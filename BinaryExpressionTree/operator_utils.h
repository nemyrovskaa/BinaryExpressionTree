#ifndef OPERATOR_H_INCLUDED
#define OPERATOR_H_INCLUDED


#include <vector>
#include <unordered_map>
#include <limits>
#include <functional>
#include <cmath>
#include <string>
#include <stdexcept>

class OperatorUtils
{
private:
    struct OperatorData
    {
        int priority;
        int identifier;
        bool is_associative;
        std::function<double(double&, double&)> calculation_func;

        // constructor of structure OperatorData
        OperatorData(int priority, int identifier, bool is_associative,
            std::function<double(double&, double&)> calculation_func)
        {
            this->priority = priority;
            this->identifier = identifier;
            this->is_associative = is_associative;
            this->calculation_func = calculation_func;
        }
    };

    // hash table of operators
    std::unordered_map<std::string, OperatorData> operators;

public:
    OperatorUtils();
    ~OperatorUtils() = default;

    bool symbIsOperator(std::string& symb);
    int getPriority(std::string& symb);
    int getIdentifier(std::string& symb);
    bool isAssociative(std::string& symb);
    std::string getSymb(int identifier);
    std::function<double(double&, double&)> getCalcFunc(std::string symb);
};


#endif // OPERATOR_H_INCLUDED