#include "Map.h"

int main() 
{
    cout << " Welcome to Kmap solver " << endl;
    int var;
    cout << " what are the number of variables that you want to solve for (3 or 4) ? ";
    cin >> var;
    while ((var != 3) && (var != 4) && (var != 2))
    {
        cout << "please choose either 2, 3 or 4 (0 to exit the program): ";
        cin >> var;
        if (var == 0) return 0;
    }

    // initializing the map
    Maps kmap(var);

    
    if (var == 4)
    {
        char choice;
        cout << " do you want a graphical kmap? (Y/N)";
        cin >> choice;
        while ((tolower(choice) != 'y') && (tolower(choice) != 'n'))
        {
            cout << "please type either Y or N (e to exit the program): ";
            cin >> choice;
            if (choice == 'e') return 0;
        }

        if (tolower(choice) == 'y')
        {
            string terms = kmap.printSimplified(1);
            kmap.printKmap(1, terms);
            
        }
        else
        {
            kmap.printKmap(0, "");
            kmap.printSimplified(0);
        }

    }
    else
    {
        kmap.printKmap(0, "");
        kmap.printSimplified(0);
    }
    

    return 0;
}