#include <iostream>
#include <string>
#include "expression_tree.h"

int showMainMenu();
int showPostfixCalcMenu();
int showInfixCalcMenu();
int showPrefixCalcMenu();
int showHelpMenu();
int showExitMenu();

void printResult(ExpressionTree& tree, double(ExpressionTree::* tree_calc_func)(std::string&), std::string& expression);
void showDirectionTitle();
void printLine();


int main()
{
    // vector of pointers on menu functions
    std::vector<std::function<int()>> menu_func = { showMainMenu, showPostfixCalcMenu,
        showInfixCalcMenu, showPrefixCalcMenu, showHelpMenu, showExitMenu };

    int option_num = menu_func[0]();
    while (option_num >= 0)
        option_num = menu_func[option_num]();

    return 0;
}


int showMainMenu()
{
    // print main menu
    system("CLS");
    std::cout << "\n\t\t\t\tWelcome to" << std::endl;
    printLine();
    std::cout << "\n\t\t\t<  Expression calculator  >" << std::endl;
    printLine();

    std::cout << "\n\n\t\t\t\t   MENU" << std::endl << std::endl;
    std::cout << "\t1. Calculate postfix expression." << std::endl;
    std::cout << "\t2. Calculate infix expression." << std::endl;
    std::cout << "\t3. Calculate prefix expression." << std::endl;
    std::cout << "\t4. Help." << std::endl;
    std::cout << "\t5. Exit." << std::endl << std::endl;

    printLine();
    std::cout << "\n\tPlease, choose the option." << std::endl;
    std::cout << "\tYour choice:  ";

    // get option
    int option_num = 0;
    std::cin >> option_num;

    // check option value and show error notification if needed
    while (option_num >= 6 || option_num < 0)
    {
        std::cout << "\n\tInvalid option. Please, enter another number:  ";
        std::cin >> option_num;
    }
    return option_num;
}


void printResult(ExpressionTree& tree, double(ExpressionTree::* tree_calc_func)(std::string&), std::string& expression)
{
    printLine();

    std::streamsize default_precision = std::cout.precision();
    std::cout.precision(std::numeric_limits<double>::max_digits10);

    // check and print the result of calculation
    try
    {
        double result = (tree.*tree_calc_func)(expression);

        if (result != result)
            std::cout << "\n\n\tThe result:  undefined" << std::endl;
        else
            std::cout << "\n\n\tThe result:  " << result << std::endl;
    }
    catch (std::invalid_argument& e)  // error notification
    {
        std::cout << "\n\n\t" << e.what() << std::endl;
    }
    catch (std::length_error& e)  // error notification
    {
        std::cout << "\n\n\t" << e.what() << std::endl;
    }

    std::cout.precision(default_precision);
}


int showPostfixCalcMenu()
{
    // print menu of postfix expression calculation
    showDirectionTitle();
    std::cout << "\n\n\t\t       Postfix expression calculation" << std::endl << std::endl;
    std::cout << "\tEnter the expression\n\n\t";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // get expression
    std::string expression;
    std::getline(std::cin, expression);

    ExpressionTree MyTree;
    printResult(MyTree, &ExpressionTree::calculatePostfixExpr, expression);

    // return to the main menu
    std::cout << "\n\n\tPress any key to return to the main menu.";
    std::cin.get();
    return 0;
}


int showInfixCalcMenu()
{
    // print menu of infix expression calculation
    showDirectionTitle();
    std::cout << "\n\n\t\t\tInfix expression calculation" << std::endl << std::endl;
    std::cout << "\tEnter the expression\n\n\t";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // get expression
    std::string expression;
    std::getline(std::cin, expression);

    // create expression tree and print the result of calculation
    ExpressionTree MyTree;
    printResult(MyTree, &ExpressionTree::calculateInfixExpr, expression);

    // return to the main menu
    std::cout << "\n\n\tPress any key to return to the main menu.";
    std::cin.get();
    return 0;
}


int showPrefixCalcMenu()
{
    // print menu of prefix expression calculation
    showDirectionTitle();
    std::cout << "\n\n\t\t\tPrefix expression calculation" << std::endl << std::endl;
    std::cout << "\tEnter the expression\n\n\t";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // get expression
    std::string expression;
    std::getline(std::cin, expression);

    // create expression tree and print the result of calculation
    ExpressionTree MyTree;
    printResult(MyTree, &ExpressionTree::calculatePrefixExpr, expression);

    // return to the main menu
    std::cout << "\n\n\tPress any key to return to the main menu.";
    std::cin.get();
    return 0;
}


int showHelpMenu()
{
    // print help menu info
    showDirectionTitle();
    std::cout << "\n\n\t\t\t\t   Help" << std::endl << std::endl;

    printLine();
    std::cout << "\n\tPostfix" << (char)179 << "\n\t" << std::string(7, (char)196) << (char)217 << std::endl << std::endl;
    std::cout << "\tEnter expression separated with gaps.\n\tExample:  2 0 + 3 * 4 -" << std::endl << std::endl;
    std::cout << "\tTo enter negative number, do not separate minus and number \n\twith gap.\n\tExample:  2 0 + 3 * -4 +" << std::endl << std::endl;

    printLine();
    std::cout << "\n\tInfix" << (char)179 << "\n\t" << std::string(5, (char)196) << (char)217 << std::endl << std::endl;
    std::cout << "\tEnter expression separated with gaps.\n\tExample:  ( 2 + 0 ) * 3 - 4" << std::endl << std::endl;
    std::cout << "\tTo enter negative number, do not separate minus and number \n\twith gap.\n\tExample:  ( 2 + 0 ) * 3 + -4" << std::endl << std::endl;

    printLine();
    std::cout << "\n\tPrefix" << (char)179 << "\n\t" << std::string(6, (char)196) << (char)217 << std::endl << std::endl;
    std::cout << "\tEnter expression separated with gaps.\n\tExample:  - * + 2 0 3 4" << std::endl << std::endl;
    std::cout << "\tTo enter negative number, do not separate minus and number \n\twith gap.\n\tExample:  + * + 2 0 3 -4" << std::endl << std::endl;

    printLine();
    std::cout << "\n\tAvailable operators" << (char)179 << "\n\t" << std::string(19, (char)196) << (char)217 << std::endl << std::endl;
    std::cout << "\tBraces:         ()\n\tSummation:       +\n\tSubtraction:     -\n\tMultiplication:  *\
            \n\tDivision:        /\n\tPower:           ^" << std::endl << std::endl;

    printLine();
    std::cout << "\n\tAvailable set of numbers" << (char)179 << "\n\t" << std::string(24, (char)196) << (char)217 << std::endl << std::endl;
    std::cout << "\tNumbers which are not belong to complex or irrational\
            \n\tset of numbers. {x " << (char)191 << "e I}, {x " << (char)191 << "e C}.\
            \n\tNumbers from interval x e {2.2e-308 ; 1.8e308}." << std::endl << std::endl << std::endl << std::endl;

    // return to the main menu
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n\tPress any key to return to the main menu.";
    std::cin.get();
    return 0;
}


int showExitMenu()
{
    // print exit menu
    showDirectionTitle();
    std::cout << "\n\n\t\t\t\t   Exit" << std::endl << std::endl;
    std::cout << "\tDo you want to exit the program?\n\tTo exit press Y\n\tOr any key to stay.";
    std::cout << "\n\n\tYour choice:  ";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    char str = std::cin.get();
    if (str != 'Y')
        return 0;  // return to the main menu
    else
        return -1;  // exit program
}


void showDirectionTitle()
{
    // print title of menu
    system("CLS");
    std::cout << std::endl << std::endl;
    printLine();
    std::cout << "\n\t\t\t<  Expression calculator  >" << std::endl;
    printLine();
}


void printLine()
{
    std::cout << "\t" << std::string(60, (char)196);
}
