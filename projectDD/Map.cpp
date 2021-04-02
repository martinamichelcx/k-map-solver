#include "Map.h"

 Maps::Maps(int v)
 {
	variables = v;
	mins = getMinterms();
	initializeMap();
 }

 vector<char> Maps::getVariables() 
 {
     vector<char> v;
     for (int i = 0; i < variables; i++)
         v.push_back(char(97 + i));
     return v;
 }

 void Maps::createSMin()
 {
     for (int i = 0; i < mins.size(); i++)
     {
         minterms.push_back(addZeros(toBinary(mins[i])));
     }
 }

 string Maps::toBinary(int n) 
 {
     if (n == 0)
         return n + "";
     if (n % 2 == 0)
         return toBinary(n / 2) + "0";
     else
         return toBinary(n / 2) + "1";
 }

 string Maps::addZeros(string term) 
 {
     int numTerms = variables - term.size();
     for (int i = 0; i < numTerms; i++)
         term = "0" + term;
     return term;
 }

 bool Maps::isConsecutive(string term1, string term2) 
 {
     bool flag = false;
     for (int i = 0; i < term1.size(); i++) {
         if (term1[i] != term2[i] && !flag)
             flag = true;
         else if (term1[i] != term2[i] && flag)
             return false;
     }
     return flag;
 }

 vector<string> Maps::removeStars()
 {
     vector<string> withoutStars;
     for (int i = 0; i < minterms.size(); i++)
     {
         string temp = "";
         for (int j = 0; j < variables; j++)
         {
             if (minterms[i][j] != '*') temp += minterms[i][j];
         }
         //cout << " the temp that i am pushing is " << temp << endl;
         withoutStars.push_back(temp);
     }

     return withoutStars;
 }

 string Maps::changeUnwanted(string term1, string term2) 
 {
     string curr = "";
     for (int i = 0; i < variables; i++)
         if (term1[i] != term2[i])
             curr = curr + "*";
         else
             curr = curr + term1[i];

     //cout << " the curr changed term is " << curr << endl;
     return curr;
 }

 vector<string> Maps::minimize() {
     vector<term> terms;
     vector<string> simplifiedTerms;

     if (minterms.size() == pow(2, variables)) return { "1" };

     for (int i = 0; i < minterms.size(); i++)
         terms.push_back({ minterms[i], 0 });

     for (int i = 0; i < minterms.size(); i++)
         for (int j = i + 1; j < minterms.size(); j++) {
             if (isConsecutive(minterms[i], minterms[j])) {
                 string changed = changeUnwanted(minterms[i], minterms[j]);
                 //cout << "the function is  " << count(simplifiedTerms.begin(), simplifiedTerms.end(), changed) << endl;
                 if (!count(simplifiedTerms.begin(), simplifiedTerms.end(), changed))
                 {
                     simplifiedTerms.push_back(changed);
                     //cout << " ana hnaaaaaaa" << endl;
                 }
                 terms[i].checked = 1;
                 terms[j].checked = 1;
             }
         }



     for (int i = 0; i < terms.size(); i++) {
         if (!terms[i].checked)
             simplifiedTerms.push_back(terms[i].val);
     }


     return simplifiedTerms;
 }

 string Maps::getImplicants(string s) {
     string term = "";
     vector<char> var = getVariables();
     for (int i = 0; i < var.size(); i++) {
         if (s[i] != '*')
         {
             if (s[i] == '0')
                 term = term + var[i] + '\'';
             else term = term + var[i];
         }
     }
     return term;
 }

 void Maps::initializeMap() 
 {
     switch (variables) {
     default:
         cout << "Invalid number of variables to draw k-map";
         break;
     case 2:
         kmap.resize(2, vector<int>(2, 0));
         break;
     case 3:
         kmap.resize(2, vector<int>(4, 0));
         break;
     case 4:
         kmap.resize(4, vector<int>(4, 0));
         break;

     }
 }

 void Maps::printKmap(bool gui, string sTerms) {
     for (int i = 0; i < mins.size(); i++)
     {
         switch (mins[i]) {
         case 0:
             kmap[0][0] = 1;
             break;
         case 1:
             kmap[0][1] = 1;
             break;
         case 2:
             kmap[0][3] = 1;
             break;
         case 3:
             kmap[0][2] = 1;
             break;
         case 4:
             kmap[1][0] = 1;
             break;
         case 5:
             kmap[1][1] = 1;
             break;
         case 6:
             kmap[1][3] = 1;
             break;
         case 7:
             kmap[1][2] = 1;
             break;
         case 8:
             kmap[3][0] = 1;
             break;
         case 9:
             kmap[3][1] = 1;
             break;
         case 10:
             kmap[3][3] = 1;
             break;
         case 11:
             kmap[3][2] = 1;
             break;
         case 12:
             kmap[2][0] = 1;
             break;
         case 13:
             kmap[2][1] = 1;
             break;
         case 14:
             kmap[2][3] = 1;
             break;
         case 15:
             kmap[2][2] = 1;
             break;
         }
     }

     if (variables == 3 || (variables == 4 && !gui))
     {
         cout << "The k-map = " << endl;
         for (int j = 0; j < kmap.size(); j++)
         {
             for (int k = 0; k < kmap[j].size(); k++)
             {
                 cout << " " << kmap[j][k] << " ";
             }
             cout << endl;
         }
     }
     else if (variables == 4 && gui)
     {
         // free memory after usage
         // important ycaptin memory el computer htri7 mnna

         RenderWindow win(VideoMode(600, 800), "4 variable kmap");

         guiMap.resize(5);
         for (int i = 0; i < 5; i++)
             guiMap[i].resize(5);

         Texture ones;
         Texture zeros;
         Texture abcd;
         Texture blank;

        if (!ones.loadFromFile("one.png"))
            cout << "error loading the image!" << endl;
         if (!zeros.loadFromFile("zero.png"))
             cout << "error loading the image!" << endl;
         if (!abcd.loadFromFile("abcd.png"))
             cout << "error loading the image!" << endl;
         if (!blank.loadFromFile("blank.png"))
             cout << "error loading the image!" << endl;
             
         int blockSize = 100;
         int emptySpace = 100;
         
         guiMap[4][4].setSize(Vector2f(blockSize, blockSize));
         guiMap[4][4].setPosition(0, 0);
         guiMap[4][4].setTexture(&abcd);

         guiMap[4][0].setSize(Vector2f(4 * blockSize, blockSize));
         guiMap[4][0].setPosition(100, 0);
         guiMap[4][0].setTexture(&blank);

         guiMap[4][1].setSize(Vector2f(blockSize, 4 * blockSize));
         guiMap[4][1].setPosition(0, 100);
         guiMap[4][1].setTexture(&blank);

         guiMap[4][2].setSize(Vector2f(blockSize, 5 * blockSize));
         guiMap[4][2].setPosition(500, 0);
         guiMap[4][2].setTexture(&blank);

         for (int i = 0; i < 4; i++)
             for (int j = 0; j < 4; j++)
             {
                 guiMap[i][j].setSize(Vector2f(blockSize, blockSize));
                 guiMap[i][j].setPosition(emptySpace + blockSize * j, emptySpace + blockSize * i);
                 if (kmap[i][j] == 0)
                 {
                     guiMap[i][j].setTexture(&zeros);
                 }
                 else
                 {
                     guiMap[i][j].setTexture(&ones);
                 }
             }
         
         
         for (int i = 0; i < 5; i++)
             for (int j = 0; j < 5; j++)
                 win.draw(guiMap[i][j], sf::RenderStates::Default);

         Font fontH;
         fontH.loadFromFile("ArialCE.ttf");

         Text simplified;
         simplified.setFont(fontH);
         simplified.setFillColor(Color::White);
         simplified.setStyle(Text::Regular);
         simplified.setCharacterSize(25);
         simplified.setPosition(20, 550);
         
         simplified.setString("y = " + sTerms);

         Text exitP;
         exitP.setFont(fontH);
         exitP.setFillColor(Color::White);
         exitP.setStyle(Text::Regular);
         exitP.setCharacterSize(30);
         exitP.setPosition(20 , 650);

         exitP.setString("type e to exit the program");

         win.draw(simplified);
         win.draw(exitP);
        

         win.display();
         
         char choice;
         cout << " type e to exit: ";
         cin >> choice;
         while ((tolower(choice) != 'e'))
         {
             cout << "type e to exit: ";
             cin >> choice;
             if (choice == 'e') return;
         }
     }
 }

 void Maps::refine()
 {

     vector<int> stars(minterms.size(), 0);

     for (int j = 0; j < minterms.size(); j++)
         for (int k = 0; k < variables; k++)
         {
             if (minterms[j][k] == '*')
                 stars[j]++;
         }
     vector<string> removed = removeStars();

     for (int i = 0; i < minterms.size(); i++)
     {
         int similar = 0;
         vector<bool> places(variables, true);


         for (int j = 0; j < minterms.size(); j++)
         {
             if (isConsecutive(removed[i], removed[j]) &&  i != j && (minterms[i].size() - stars[i]) >= (minterms[j].size() - stars[j]) )
             {
                 for (int k = 0; k < variables; k++)
                 {
                     if (minterms[i][k] == minterms[j][k] && minterms[i][k] != '*' && places[k])
                     {
                         similar++;
                         places[k] = false;
                     }

                 }
             }
         }

         if (similar == variables - stars[i])
         {
             minterms.erase(minterms.begin() + i);
             stars.erase(stars.begin() + i);
             removed.erase(removed.begin() + i);

             //i--;
         }
    }
 }

 vector<int> Maps::getMinterms() {

     vector<int> minterms;
     std::cout << "enter the minterms then -1 (as separated values e.g. 1 2 5 -1): ";
     int c;
     set<int> exists;
     int count = 1;

     do 
     {
         cin >> c;
         
         if (  c < -1 || c > pow(2, variables) || !cin.good())
         {
             cin.clear();
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
             std::cout << "Please enter a minterm within the limits: ";
         }
         else
         {   
             if (minterms.size() != pow(2, variables) && !exists.count(c) && c != -1)
             {
                 minterms.push_back(c);
                 exists.insert(c);
                 count++;
             }
         }
     } while (c != -1 && count <= pow(2, variables));

     return minterms;
 }

 string Maps::printSimplified(bool gui)
 {
     createSMin();
     minterms = minimize();
     if (minterms[0] == "1")
     {
         cout << "y = 1" << endl;
         return "1";
     }
     sort(minterms.begin(), minterms.end());
     while (!VectorsEqual(minterms, minimize()))
     {
         sort(minterms.begin(), minterms.end());
         minterms = minimize();
     }

     refine();

     string sTerms = "";
     for (int i = 0; i < minterms.size() - 1; i++)
         sTerms += getImplicants(minterms[i]) + " + ";
     sTerms += getImplicants(minterms[minterms.size() - 1]);
     
     if (!gui) {
         
         cout << "y = " << sTerms << endl;
         return sTerms;
     }
     else
     {
         return sTerms;    
     }
 }

 bool Maps::VectorsEqual(vector<string> a, vector<string> b)
 {
     if (a.size() != b.size())
         return false;

     sort(a.begin(), a.end());
     sort(b.begin(), b.end());
     for (int i = 0; i < a.size(); i++)
     {
         if (a[i] != b[i])
             return false;
     }
     return true;
 }