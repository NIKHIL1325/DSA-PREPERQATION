#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <queue>
using namespace std;

class stock
{
private:
    string logo;
    string name;
    int quantity;
    double buyprice;
    double currentprice;

public:
    stock(string l, string n, int q, double p)
    {
        logo = l;
        name = n;
        quantity = q;
        buyprice = p;
          currentprice = p;
    }

    string getlogo()
    {
        return logo;
    }

    string getName()
    {
        return name;
    }

    int getQuantity()
    {
        return quantity;
    }

    double getBuyPrice()
    {
        return buyprice;
    }



    void setcurrentprice(double price){
        currentprice = price;
    }

    double getCurrentPrice() {
    return currentprice;
}

    void addQuantity(int amount)
    {
        quantity += amount;
    }
    void sellQuantity(int amount)
    {
        quantity -= amount;
    }
};

class Transaction
{
private:
    string action;
    string symbol;
    int quantity;
    double price;

public:
    Transaction() {};
    Transaction(string a, string s, int q, double p)
    {
        action = a;
        symbol = s;
        quantity = q;
        price = p;
    }

    void display()
    {
        cout << action << " | "
             << symbol << " | "
             << quantity << " | "
             << price << endl;
    }
};

class TransactionNode
{
private:
public:
    Transaction data;
    TransactionNode *next;
    TransactionNode(Transaction t)
    {
        data = t;
        next = nullptr;
    }
};

void addTransaction(TransactionNode *&head,
                    string action, string symbol,
                    int quantity, double price)
{

    Transaction t(action, symbol, quantity, price);

    TransactionNode *node = new TransactionNode(t);

    node->next = head;
    head = node;
}

void viewportfolio(unordered_map<string, stock> &portfolio)
{
    if (portfolio.empty())
    {
        cout << "PORTFOLIO IS EMPTY !" << endl;
        return;
    }
    cout << "\n----MY STOCK PORTFOLIO-----\n";
    for (auto it = portfolio.begin(); it != portfolio.end(); it++)
    {
        cout << "Symbol: " << it->first << endl;
        cout << "company : " << it->second.getName() << endl;
        cout << "quantity : " << it->second.getQuantity() << endl;
        cout << "buy price : " << it->second.getBuyPrice() << endl;
        cout << "Current price: " << it->second.getCurrentPrice() << endl;
        cout << endl;
    }
}


void analyzeProfitLoss(unordered_map<string, stock>& portfolio)
{
    if (portfolio.empty())
    {
        cout << "Portfolio is empty!\n";
        return;
    }

    cout << fixed << setprecision(2);


    double totalinvext =0;
    double currentval=0;
    
   for (auto it = portfolio.begin(); it != portfolio.end(); it++){
   double quantity = it->second.getQuantity();
double buyPrice = it->second.getBuyPrice();
double currentPrice = it->second.getCurrentPrice();

double investment = quantity * buyPrice;
double currentValue = quantity * currentPrice;
double profitLoss = currentValue - investment;

double returnPercent = 0;

if (investment > 0)
{
    returnPercent = (profitLoss / investment) * 100;
}

totalinvext += investment;
currentval += currentValue;

cout << "\nStock: " << it->first << endl;
cout << "Investment: " << investment << endl;
cout << "Current Value: " << currentValue << endl;
cout << "Profit/Loss: " << profitLoss << endl;
cout << "RETURN : " << returnPercent << endl;

   }

   double totalProfitLoss = currentval - totalinvext;

cout << "\n===== PORTFOLIO SUMMARY =====\n";
cout << "Total Investment: " << totalinvext << endl;
cout << "Total Current Value: " << currentval << endl;
cout << "Overall Profit/Loss: " << totalProfitLoss << endl;

if (totalProfitLoss > 0)
    cout << "You are in PROFIT!\n";
else if (totalProfitLoss < 0)
    cout << "You are in LOSS!\n";
else
    cout << "No Profit, No Loss!\n";

    // 1. Total investment ke liye variable banao
    // 2. Total current value ke liye variable banao

    // 3. map ke har stock par loop lagao

    // 4. Investment calculate karo
    // 5. Current value calculate karo
    // 6. Profit/Loss calculate karo

    // 7. Har stock ka result display karo

    // 8. Overall totals aur profit/loss display karo
}

void updateCurrentPrice(unordered_map<string, stock>& portfolio)
{
    string symbol;
    double price;

      cout << "Enter symbol of company whose stock price changed " << endl;
    cin >> symbol;
    // 1. Symbol input lo
    auto it = portfolio.find(symbol);
    if (it == portfolio.end())
    {
        cout << "STOCK NOT FOUND" << endl;
        return;
    }

    // 2. map mein stock search karo


    // 3. Stock nahi mile toh return karo

    // 4. New price input lo

    cout << "Enter NEW PRICE buy: \n";
    cin >> price;
    
    // 5. Invalid price check karo
    if (price <= 0)
    {
        cout << "NOT VALID STOCK TO BUY\n";
        return;
    }


    // 6. Current price update karo
    it->second.setcurrentprice(price);

    cout<<"\nPRICE UPDATED SUCCESFULLY\n"<<endl;
}

void addStock(unordered_map<string, stock> &portfolio)
{
    string symbol, name;
    int quantity;
    double price;

    cout << "Enter symbol of company to add " << endl;
    cin >> symbol;

    if (portfolio.find(symbol) != portfolio.end())
    {
        cout << "STOCK ALREADY EXITS " << endl;
        return;
    }

    cout << "Enter NAME of STOCK to add " << endl;
    // cin>>name;
    cin.ignore();
    getline(cin, name);
    cout << "Enter PRICE  of STOCK to add " << endl;
    cin >> price;
    cout << "Enter QTY of STOCK to add " << endl;
    cin >> quantity;

    if (quantity <= 0 || price <= 0)
    {
        cout << "Invalid quantity or price!\n";
        return;
    }

    stock s(symbol, name, quantity, price);

    portfolio.emplace(symbol, s);

    cout << "Stock added successfully!\n";

    // 1. User se symbol input lo
    // 2. Check karo symbol pehle se exist karta hai ya nahi
    // 3. Name, quantity aur price input lo
    // 4. Stock object banao
    // 5. Map mein insert karo
}

void buystock(unordered_map<string, stock> &portfolio, TransactionNode *&head)
{
    string symbol;
    int amount;

    cout << "Enter stock symbol to buy: ";
    cin >> symbol;

    auto it = portfolio.find(symbol);
    if (it == portfolio.end())
    {
        cout << "STOCK NOT FOUND" << endl;
        return;
    }

    cout << "Enter quantity to buy: \n";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "NOT VALID STOCK TO BUY\n";
        return ;
    }

    (it->second).addQuantity(amount);

    cout << "Shares purchased successfully!\n";

    addTransaction(head, "BUY", symbol, amount,
                   it->second.getBuyPrice());
}

void sellstockquantity(unordered_map<string, stock> &portfolio, TransactionNode *&head)
{
    string symbol;
    int amount;

    cout << "Enter stock symbol to SELL: ";
    cin >> symbol;

    auto it = portfolio.find(symbol);
    if (it == portfolio.end())
    {
        cout << "STOCK NOT FOUND" << endl;
        return;
    }

    cout << "Enter quantity to sell: \n";
    cin >> amount;

    if (amount <= 0)
    {
        cout << "NOT VALID STOCK TO BUY\n";
        return;
    }
    if (amount > it->second.getQuantity())
    {
        cout << "NOT AVAILABE THIS QTY STOCKS \n";
        return;
    }

    (it->second).sellQuantity(amount);

    cout << "Shares sold successfully!\n";

    addTransaction(head, "SELL", symbol, amount,
                   it->second.getBuyPrice());
}

void viewHistory(TransactionNode *head)
{
    if (head == nullptr)
    {
        cout << "Transaction history is empty!\n";
        return;
    }

    TransactionNode *temp = head;

    cout << "\n--- TRANSACTION HISTORY ---\n";

    while (temp != nullptr)
    {
        temp->data.display();
        temp = temp->next;
    }
}

void saveportfolio(unordered_map<string, stock> &portfolio)
{
    ofstream file("portfolio.txt");

    if (!file.is_open())
    {
        cout << "File open nahi hui!\n";
        return;
    }

    for (auto it = portfolio.begin();
         it != portfolio.end(); it++)
    {

        file << it->first << '\n';
        file << it->second.getName() << '\n';
        file << it->second.getQuantity() << '\n';
        file << it->second.getBuyPrice() << '\n';
        file << it->second.getCurrentPrice() << '\n';
    }

    file.close();
    cout << "Portfolio saved successfully!\n";
}
void loadPortfolio(unordered_map<string, stock> &portfolio)
{
    ifstream file("portfolio.txt");

    if (!file.is_open())
    {
        cout << "Portfolio file nahi mili!\n";
        return;
    }

    string symbol, name;
    int quantity;
    double buyprice,currentprice;

    while (getline(file, symbol))
    {
        if (!getline(file, name))
            break;
        if (!(file >> quantity >> buyprice>>currentprice))
            break;
        file.ignore();

        stock s(symbol, name, quantity, buyprice);
        s.setcurrentprice(currentprice);
        portfolio.emplace(symbol, s);
    }

    file.close();

    cout << "Portfolio loaded: "
         << portfolio.size() << " stocks\n";
}


double calculateStockProfit(stock &s)
{
    return s.getQuantity() *
           (s.getCurrentPrice() - s.getBuyPrice());
}

void mergeStocks(vector<pair<string, double>> &stocks,
                 int left, int mid, int right)
{
    vector<pair<string, double>> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (stocks[i].second >= stocks[j].second)
            temp.push_back(stocks[i++]);
        else
            temp.push_back(stocks[j++]);
    }

    while (i <= mid)
        temp.push_back(stocks[i++]);

    while (j <= right)
        temp.push_back(stocks[j++]);

    for (int k = 0; k < (int)temp.size(); k++)
        stocks[left + k] = temp[k];
}

void mergeSortStocks(vector<pair<string, double>> &stocks,
                     int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSortStocks(stocks, left, mid);
    mergeSortStocks(stocks, mid + 1, right);

    mergeStocks(stocks, left, mid, right);
}

vector<pair<string, double>> collectStockProfits(
    unordered_map<string, stock> &portfolio)
{
    vector<pair<string, double>> stocks;

    for (auto &item : portfolio)
    {
        double profit = calculateStockProfit(item.second);
        stocks.push_back({item.first, profit});
    }

    return stocks;
}

void sortStocksByProfit(
    unordered_map<string, stock> &portfolio)
{
    if (portfolio.empty())
    {
        cout << "Portfolio is empty!\n";
        return;
    }

    vector<pair<string, double>> stocks =
        collectStockProfits(portfolio);

    mergeSortStocks(stocks, 0, (int)stocks.size() - 1);

    cout << fixed << setprecision(2);
    cout << "\n--- STOCKS SORTED BY PROFIT/LOSS ---\n";

    for (auto &item : stocks)
    {
        cout << item.first
             << " | Profit/Loss: Rs. "
             << item.second << '\n';
    }
}


void showTop3Stocks(unordered_map<string, stock> &portfolio)
{
    if (portfolio.empty())
    {
        cout << "Portfolio is empty!\n";
        return;
    }

    vector<pair<string, double>> stocks =
        collectStockProfits(portfolio);

    // Priority queue mein {profit, symbol} store hoga.
    vector<pair<double, string>> heapData;

    for (auto &item : stocks)
    {
        heapData.push_back({item.second, item.first});
    }

    // Vector se max-heap construct hota hai.
    priority_queue<pair<double, string>> pq(
        heapData.begin(), heapData.end());

    cout << fixed << setprecision(2);
    cout << "\n--- TOP 3 STOCKS BY PROFIT/LOSS ---\n";

    int count = 0;

    while (!pq.empty() && count < 3)
    {
        auto top = pq.top();
        pq.pop();

        cout << count + 1 << ". "
             << top.second
             << " | Profit/Loss: Rs. "
             << top.first << '\n';

        count++;
    }
}



int main()
{
    // system("cls");
    // map<string,stock> portfolio;

    // stock s1("TCS","tatasteel",5,3500.0);
    // portfolio.emplace("TCS",s1);
    // system("cls");
    // if(portfolio.find("TCS") != portfolio.end()){
    //     cout<<"STOCK FOUND "<<s1.getName()<<endl;
    // }

    // auto it = portfolio.find("TCS");

    // if(it != portfolio.end()){
    //    cout << it->second.getName() << endl;
    // cout << it->second.getQuantity() << endl;

    // }
    // viewportfolio(portfolio);
    // addStock(portfolio);
    // viewportfolio(portfolio);

    int choice;
    unordered_map<string, stock> portfolio;
    // vector<Transaction> history;
    TransactionNode *head = nullptr;

    loadPortfolio(portfolio);
    do
    {

        cout << "\n===== STOCK PORTFOLIO =====\n";
        cout << "1. Add Stock\n";
        cout << "2. View Portfolio\n";
        cout << "3. BUY stock\n";
        cout << "4. sell stock \n";
        cout << "5. View Transaction History\n";
        cout << "6. update stock price\n";
        cout << "7. ANALYZER \n";
        cout << "8. Exit\n";
        cout << "9. Sort Stocks by Profit/Loss\n";
cout << "10. Show Top 3 Stocks\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStock(portfolio);
            break;

        case 2:
            viewportfolio(portfolio);
            break;

        case 3:
            buystock(portfolio, head);
            break;

        case 4:
            sellstockquantity(portfolio, head);
            break;
        case 5:
            viewHistory(head);
            break;

            case 6:
    updateCurrentPrice(portfolio);
    break;
            
            case 7:
             analyzeProfitLoss(portfolio);
    break;
    
        case 8:
            saveportfolio(portfolio);
            cout << "exiting program..\n";
            break;


case 9:
    sortStocksByProfit(portfolio);
    break;

case 10:
    showTop3Stocks(portfolio);
    break;

        default:
            cout << "INVALID choice!\n ";
        }

    } while (choice != 8);

    while (head != nullptr)
    {
        TransactionNode *temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
