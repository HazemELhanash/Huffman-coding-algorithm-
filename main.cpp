#include <iostream>
#include <string.h>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

struct Node
{
    char ch;
    int freq;
    Node * left , *right;
};

struct comp
{
    bool operator()(Node* l, Node* r)
    {
        return (l->freq > r->freq);
    }
};

Node* getNode(char ch , int freq , Node* left , Node* right);
float buildHuffmanTree(string text);
void encode(Node* root , string str , unordered_map<char, string> &huffmanCode);
string convert (char c);
void decode (Node* root , int &top_index , string str);

int main()
{
    string text,name,paragraph;
    float ratio=0.0;
    //for creating the file

    //name of instance
    ofstream file("Hazem.txt");
   // cout<<"enter text"<<endl;
   // cin>>paragraph;
    file << "check card                      The bank validates the credit card\
counter time upload             A counter that counts down to explain when the auction will start\
when end                        The auction end time is displayed and a countdown is made over the remaining time until the end of the auction\
Time raising                    Increase the time automatically for 24 hours in case the value of the bids does not reach the minimum price of the product in order for the seller to communicate with the highest person who raised the price if he wants to sell it to him\
email                           Mail is sent to the seller at the end of the auction with the data of the highest bidder and after the completion of the sale to confirm the arrival of the amount to him\
total cost                      Calculating the total amount to be paid by the buyer including the price of the product in addition to the price of the product shipping\
track                           Determine where the product is received from the seller and where it is delivered to the buyer and calculate the required value for shipment follow the route of the cargo journey and inform the buyer in case of a problem the shipment has been delayed\
save money at the company       You save the amount paid by the buyer until the product is successfully delivered and then send the amount to the seller\
web                             The platform on which the auction will be published is a website\
history                         The sellers history is displayed in terms of the number of successful sales and purchases and the date of its start of use of the auction site and its personal data in order to communicate with it\
initial price and higher price  The minimum start of the auction and the maximum price are shown in order to buy the product now\
status of bid                   Product data appears in the auction list such as his name and picture in case of a new condition or a user and in good condition or not\
notification                    Send notices of the latest updates about the product offered or bid";
    file.close();

    ifstream MyReadFile("Hazem.txt");
    while(getline(MyReadFile, text)) ;
     float file_size_after = buildHuffmanTree(text);
    cout<<endl;

   ifstream my_file("Hazem.txt" , ios::binary);
   my_file.seekg(0, ios::end);
    float file_size_before = my_file.tellg()*8;
    cout<<"file size_before"<<"    "<< file_size_before <<endl;
    cout<<"file size_after"<<"    "<< file_size_after <<endl;

    ratio= ((file_size_before-file_size_after)/file_size_before)*100;
    cout<<"SO RATIO OF COMPRESSION = "<< ratio <<"%"<<endl;


//buildHuffmanTree(text);

return 0 ;
}

Node* getNode(char ch , int freq , Node* left , Node* right)
{
   Node* node = new Node();

    node->ch =ch;
    node->freq=freq;
    node->left =left;
    node->right = right;

    return node;
}


void encode(Node* root , string str , unordered_map<char, string> &huffmanCode)
{
    if(root==NULL)
    {
        return;
    }

    if ( !root->left && !root->right)
    {
        huffmanCode[root->ch]=str;
    }
    encode(root->left,str+ "0", huffmanCode);
    encode(root->right,str+ "1", huffmanCode);

}


string decode (Node* root , string str)
{
    string ans = "";
    Node* curr = root;
    for (int i=0;i<str.size();i++)
    {
        if (str[i] == '0')
           curr = curr->left;
        else
           curr = curr->right;

        // reached leaf node
        if (curr->left==NULL and curr->right==NULL)
        {
            ans += curr->ch;
            curr = root;
        }
    }
    // cout<<ans<<endl;
    return ans+'\0';


}

string convert (char c)
{

        int val= int(c);

        string bin = "";
        while (val > 0)
        {
            if(val % 2 ==1)
                bin+="1";
            if (val % 2 == 0)
                bin+="0";
             val/=2;
        }
        bin+="0";
        reverse(bin.begin() , bin.end());
        return bin ;
}


float buildHuffmanTree(string text)
{
    int size_before=0;


    unordered_map <char , int > freq ;
    for(char ch : text)
    {
        freq[ch]++;
    }


    priority_queue <Node* , vector<Node*> , comp> pq ;

    for(auto pair : freq)
    {
        pq.push(getNode(pair.first , pair.second , NULL , NULL));
    }

    while(pq.size() != 1)
    {

       Node* left =pq.top();     pq.pop();
        Node* right=pq.top();     pq.pop();

       int sum = left->freq + right->freq ;
        pq.push(getNode('\0', sum , left , right));
    }

    Node* root =pq.top();

    unordered_map <char , string> huffmanCode;
    encode(root, "", huffmanCode);

    for(auto pair : huffmanCode)
    {
       string binary =convert(pair.first);
        cout<<"Character"<<"   "<< "Original Code"<<"    "<<"Huffman Code"<<endl;
        cout<<'\n';
        cout<<pair.first<<"             "<< binary<< "           "<< pair.second<< '\n';
        cout<<'\n';
    }

    cout<<"The original string was -->"<<"  " << text<< '\n';
    cout<<"-----------------"<< '\n';
    cout<<"The encoded string is -->"<<'\n';
    string str="";
    for(char ch :text)
    {
        str+=huffmanCode[ch];
    }
    cout<<str<<endl;


    cout<<"Decoded String is -- > "<<endl<<endl;
    cout<< decode(root,str)<<endl;

   //to find out size of file after compression
    ofstream file("Compressed.txt");
    file << str;
    file.close();

   ifstream my_file("Compressed.txt" , ios::binary);
   my_file.seekg(0, ios::end);
    int file_size_after = my_file.tellg();

    return file_size_after;
  }





