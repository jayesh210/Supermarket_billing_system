#include<iostream>
#include<conio.h>
#include<fstream>
#include<string.h>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;
int pass,t,counter=0;
float gtotal=0;
void admin_account()
{
system("cls");
  int ctr=0;
  int  o;
  char pass[9];

  cout<<"Enter password :";
  for(int i=0;i<8 && (o=getch())!=13  ;i++)
  {  
    pass[i]=o;

    putch('*');
  }
  ctr=strcmp(pass,"admin123");
  if(ctr==0)
  {
    cout<<"\n Authorised";
    t=0;
  }
  else
  {
    cout<<"\n Wrong password \nYou typed :"<<pass;
    t=1;
  }
  getch();
  
}
class item
{
	int Item_no;
	char Name[25];
	int dd,mm,yy,qty;
	float price,tax,amt,namt;
	
	public:
    void add()  // FUNCTION TO ADD ITEMS
    {
    	system("cls");
        cout<<"\n\n\tItem No: ";
        cin>>Item_no;
        cin.ignore();
        cout<<"\n\n\tName of the item: ";
        cin.getline(Name,25);
        cout<<"\n\n\tManufacturing Date(dd-mm-yy): ";
        cin>>dd>>mm>>yy;
         cout<<"\n\n\tPrice: ";
    cin>>price;
      cout<<"\n\n\tQuantity: ";
    cin>>qty;
    cout<<"\n\n\tTax percent: ";
    cin>>tax;
    namt=price+(price*(tax/100));
    amt=namt*qty;
    }
    void show()  // TO SHOW ITEM DATA
    {
        cout<<"\n\tItem No: ";
        cout<<Item_no;
        cout<<"\n\tName of the item: ";
        cout<<Name;
        cout<<"\n\tDate : ";
        cout<<dd<<"-"<<mm<<"-"<<yy;
        cout<<"\n\tPrice per item: ";
        cout<<price;
        cout<<"\n\tQuantity: ";
        cout<<qty;
        cout<<"\n\tTax percent: ";
        cout<<tax;
        cout<<"\n\tNet amount: ";
        cout<<amt;
        
    }
    void bill_show() // TO SHOW BILL DETAIL
    {
        cout<<"\n"<<Item_no<<"\t\t"<<Name<<"\t"<<price<<"\t\t"<<qty<<"\t"<<tax<<" %\t"<<amt;
    	 
	}
    void store()
    {
    	ofstream fout;
    	fout.open("file1.dat",ios::app|ios::binary);
    	fout.write((char*)this,sizeof(*this));
    	fout.close();
   }
   void view_item() //TO CHECK STOCK DATA
   {
   	system("cls");
    cout<<"\n\t\t*********************************************";
    cout<<"\n\t\t                 DETAILS                     ";
    cout<<"\n\t\t*********************************************\n\n\n";
	cout<<"ITEM NO."<<"\t"<<"NAME"<<"\t"<<"PRICE"<<" \t  "<<"Quantity"<<"\t"<<"TAX %"<<"\t"<<"NET AMOUNT\n\n";
   	ifstream fin;
   	fin.open("file1.dat",ios::in|ios::binary) ;
	   if(!fin)
	   cout<<"\n Record not found";
	   else
	   {
	   	fin.read((char*)this,sizeof(*this));
	   	while(!fin.eof())
		   {
		   		bill_show();
		   		fin.read((char*)this,sizeof(*this));
		   	
		   		
		   }
		   	getch();
		   fin.close();
	   }
   }
   void search_item(char*t)
   {
   	ifstream fin;
   	fin.open("file1.dat",ios::in|ios::binary);
   	if(!fin)
	   cout<<"\n File not found";
	else
	{
		fin.read((char*)this,sizeof(*this));
		while(!fin.eof())
		   {
		   	if(!strcmp(t,Name))
		   	{
		   		show();
		   		getch();
		   		counter++;
			   }
			   fin.read((char*)this,sizeof(*this));
		   }fin.close();
		   if(counter==0)
		   cout<<"\n Record not found";
		   
	}
   	
   }
   void delete_item(char*t)    //DELETE ITEM RECORD
   {
   
   	ifstream fin;
   	ofstream fout;
   	fin.open("file1.dat",ios::in|ios::binary);
   	
   	if(!fin)
   	   cout<<"\n File not found";
   	else
   	{
   		fout.open("tempfile.dat",ios::out|ios::binary);
   		fin.read((char*)this,sizeof(*this));
   		while(!fin.eof())
   		{
   		if(strcmp(Name,t))
   		fout.write((char*)this,sizeof(*this));
   		fin.read((char*)this,sizeof(*this));
		}
		fin.close();
		fout.close();
		remove("file1.dat");
		rename("tempfile.dat","file1.dat");		
		}
   	
   }
   void update(char *s)
   {
   	int I=0;
   	fstream file;
   	file.open("file1.dat",ios::ate|ios::in|ios::out|ios::binary);
   	file.seekg(0);
   	I++;
   	file.read((char*)this,sizeof(*this));
   	while(!file.eof())
   	{
   	
   		if(!strcmp(s,Name))
   		{
   			add();
   			I--;
   			file.seekp(I*sizeof(*this));  
   			file.write((char*)this,sizeof(*this));
		}
		I++;
		file.read((char*)this,sizeof(*this));
   		
	}
	file.close();
   }
   void calculate_bill()
    {
    	ofstream fout;
    	fout.open("xy.dat",ios::app|ios::binary);
    	fout.write((char*)this,sizeof(*this));
    	fout.close();
   }void sold_item()
    {
    	ofstream fout;
    	fout.open("ab.dat",ios::app|ios::binary);
    	fout.write((char*)this,sizeof(*this));
    	fout.close();
   }
  
   void calculate_show() // FINAL BILL
   {
   	system("cls");
	cout<<"\t\t\tINVOICE\n ";
	cout<<"\t\t\t=======\n\n\n";
	cout<<"ITEM NO."<<"\t"<<"NAME"<<"\t"<<"PRICE"<<" \t"<<"TAX %"<<"\t  "<<"NET AMOUNT\n\n";
   	ifstream fin;
   	fin.open("xy.dat",ios::in|ios::binary) ;
	   if(!fin)
	   cout<<"\n File not found";
	   else
	   {
	   	fin.read((char*)this,sizeof(*this));
	   	gtotal=0;
	   	while(!fin.eof())
	{
		bill_show();
		gtotal+=amt;
		fin.read((char*)this,sizeof(*this));
	}
		getch();
		   	 cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;
		   fin.close();
	   }
   }
   void sold_show() //TO CHECK SOLD DATA
   {
   	system("cls");
	cout<<"\t\t\tBilling System\n ";
	cout<<"\t\t\t==============\n\n\n";
	cout<<"ITEM NO."<<"\t"<<"NAME"<<"\t"<<"PRICE"<<" \t"<<"TAX %"<<"\t  "<<"NET AMOUNT\n\n";
   	ifstream fin;
   	fin.open("ab.dat",ios::in|ios::binary) ;
	   if(!fin)
	   cout<<"\n File not found";
	   else
	   {
	   	fin.read((char*)this,sizeof(*this));
	   	while(!fin.eof())
		   {
		   		bill_show();
		   		fin.read((char*)this,sizeof(*this));
		   	
		   		
		   }
		   	getch();
		   fin.close();
	   }
   }
   
  
};


int main()
{
	
	cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout<<setprecision(1);
	item i1;
	char Name[20];
menu:	system("cls");
	cout<<"\t\t\tSuper Market Billing\n ";
	cout<<"\t\t\t====================\n\n\n";
	cout<<"\t\t1.ADMINISTRATOR ACCOUNT\n\n";
    cout<<"\t\t2.BILLER ACCOUNT\n\n";
    cout<<"\t\t3.EXIT\n\n";
 r :    cout<<"\n\t\tPlease Enter Required Option: ";
    int c;
    cin>>c;
	switch(c)     //Choice number one for accounts and exit
	{ 
	case 1: //FOR ADMIN ACCOUNT
	{
	admin_account();
	if(t==0)
	{
aa:	system("cls");
        cout<<"\t\t\tITEM ANALYSIS\n ";
    	cout<<"\t\t\t=============\n\n\n";
        cout<<"\n\t\t1.Stock Check\n\n";
        cout<<"\t\t2.Add item record\n\n";
        cout<<"\t\t3.Change item record\n\n";
        cout<<"\t\t4.Delete item record\n\n";
        cout<<"\t\t5.Sold item\n\n";
        cout<<"\t\t6.Search item\n\n";
        cout<<"\t\t7.Go to previous page\n\n";
      cout<<"\t\tPlease Enter Required Option: ";
        int coo;
        cin>>coo;
	switch(coo)
	{
		case 1:  //STOCK CHECK
        {
        i1.view_item();
        getch();
 
        goto aa;
        break;
		}
		case 2:  //ADD ITEM RECORDS
        {
    
a:	    i1.add();
        getch();
	    i1.show();
	        getch();
	    i1.store();
	    system("cls");
	    cout<<"\nWANT TO ADD MORE(Y/N)?\n";
	    char D;
	        	cin.ignore();
	    cin>>D;
	    if((D=='Y')||(D=='y'))
	    {
	    	goto a;
		}
		else
		
		       cout<<"\n\t\tItem Added Successfully!";
		       getch();
		goto aa;
 		     break;
		}
		case 3: //CHANGE ITEM RECORD
        {
        	system("cls");
        	cout<<"\nEnter item name to update records :";
        	cin.ignore();
        	cin.getline(Name,19);
        	i1.update(Name);
        	cout<<"\n\t\tItem Succesfully Updated";
        	getch();
        	goto aa;
        	
        break;
		}
		case 4: // DELETE ITEM RECORD
        {
        	getch();
        	system("cls");
        	cout<<"\nEnter the name of item to delete record:";
        	cin.ignore();
        	cin.getline(Name,19);
        	i1.delete_item(Name);
        	i1.view_item();
        	cout<<"\n\n\t\tItem Succesfully Deleted";
        	getch();
        	goto aa;
        break;
		}
		case 5: // SOLD ITEM
        {
        	i1.sold_show();
        	getch();
        	goto aa;
        
        break;
		} 
		case 6:  // SEARCH ITEM RECORD
        {
        	system("cls");
        	cout<<"\nEnter the name of item to search record:";
        	cin.ignore();
        	cin.getline(Name,19);
        i1.search_item(Name);
        goto aa;
        break;
		}
		case 7:  // GOTO PREVIOUS PAGE
        {
        goto menu;
        break;
		}
	  
	}
}
	else  // ELSE CONDITION FOR WRONG PASSWORD
	{
		cout<<"\nUNAUTHOTISED";
		goto menu;
	}
    break;			
	}
	case 2: //USER ASCCOUNT
	{
	bb:	system("cls");
    cout<<"\t\t\tBILLING\n ";
    cout<<"\t\t\t=============\n\n\n";
    cout<<"\n\t\t1.Calculate Bill\n\n";
    cout<<"\t\t2.Go to previous page\n\n";
    cout<<"\t\tPlease Enter Required Option: ";
    int cs;
    cin>>cs;
    switch(cs) //CHOICE UNDER  USER ACCOUNTS
    {
        case 1: // CALCULATE BILL
        {
 z:	        system("cls");
        	cout<<"\nEnter the name of item to search record:";
        	cin.ignore();
        	cin.getline(Name,19);
            i1.search_item(Name);
            i1.calculate_bill();
            i1.sold_item();
            i1.delete_item(Name);
            system("cls");
        cout<<"YOU WANT TO ADD MORE (Y/N)?";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            system("cls");
            goto z;
           
        }
        else if((yn=='N')||(yn=='n'))
        {
        	i1.calculate_show();
        	getch();
        	remove("x.dat");
	        goto bb;
         }

 break;
		}
		case 2: // GOTO PREVIOUS PAGE
        {
        goto menu;
        break;
		}
	}
		
	break;
	}
	case 3:     // EXIT
	{    system("cls");
        cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            system("cls");
            cout<<"************************** THANKS **************************************";
            getch();
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        else
        {
            goto menu;
        }}
    default:
        cout<<"\n\n\t\tWrong Choice....Please Retry!";
        getch();
        goto r;
        break;
}
}
