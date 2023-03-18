/*
C++ Code on Page Replacement Algorithms

Team Members:

1.	Durga Naga Sai Sireesha Valluri 
2.	Mohammed Mudasir Shaik
3.	Mounika Dandiboina 
4.	Vasavi Maddi
*/

#include<bits/stdc++.h>
#include <iostream>

//Defining all the function used in the program	

void FIFO();
void optimalPageReplacement();
void LRUPageReplacement();
void LFUPageReplacement();
void MFUAlgorithm();
void enhancedSecondChance();
int menu();
int findpos(int[], int, int[], int, int);
int LFU(int[], int, int);
int MFU(int[], int, int);
int presentESA(int[], int, int, int[]);
	
#define FRAMES_NUMBER 3

using namespace std;

int main()
{
	int selectOne = 0;
	selectOne = menu();
	
	while (selectOne != 7) //It will showing the menu until 7 is entered by the user to exit
	{				
		switch (selectOne)
		{
			case 1: cout << "\nYou selected FIFO Page Replacement Algorithm from the menu\n";
					FIFO();
					break;
			case 2: cout << "You selected Optimal Page Replacement Algorithm from the Menu\n";
					optimalPageReplacement();
					break;
			case 3: cout << "You selected LRU page replacement Algorithm from the Menu\n";
					LRUPageReplacement();
					break;
			case 4: cout << "You selected LFU page Replacement Algorithm from the Menu\n";
					LFUPageReplacement();
					break;
			case 5: cout << "You selected MFU Algorithm from the Menu\n";
					MFUAlgorithm();
					break;
			case 6: cout << "You selected Enhanced second chance Algorithm from the Menu\n";
					enhancedSecondChance();
					break;
			default: cout<< "You have selected an invalid option \n";
					 break;			
		}
		selectOne = menu();
	}
	return 0;
}

//Menu list asking user to select any one Page Replacement Algorithm
int menu()
{
	int selectOne;
	
		cout << "\nSelect any of the following Page replacement algorithms:\n";
		cout << "1. FIFO Page Replacement Algorithm \n";
		cout << "2. Optimal Page Replacement Algorithm\n";
		cout << "3. LRU page replacement Algorithm\n";
		cout << "4. LFU page Replacement Algorithm\n";
		cout << "5. MFU Algorithm\n";
		cout << "6. Enhanced second chance Algorithm\n";
		cout << "7. exit\n";
		
		cin >> selectOne;

 return selectOne;
}

int present(int table_frame[], int nf, int page)
{
	for(int i = 0; i < nf; i++)
		if(page == table_frame[i])
			return 1;
	return 0;
}

void printtable(int table_frame[], int nf)
{
	for(int i = 0; i < nf; i++)
	{
		if(table_frame[i] == -1)
			printf("-- ");
		else
			printf("%2d ", table_frame[i]);
	}
	printf("||");
}

void FIFO()
{
	//nf-number of frames
    int n,nf,i,pos=0;

    printf("Enter the number of frames\n");
    scanf("%d",&nf);
	
    int table_frame[nf];
    for(i=0;i<nf; i++)
    {
        table_frame[i]=-1;
    }


    printf("Enter the total number of page requests\n");
    scanf("%d",&n);
    int pages[n];
    printf("Enter the reference string\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }


    int count1=0;
    printf("Position of frame table after each request\n");
    for(i=0;i<n;i++)
    {
        printf("Page table after request from %2d || ",pages[i]);
        if(!present(table_frame,nf,pages[i]))
        {
           table_frame[pos] = pages[i];
           pos = (pos+1)%nf ;//considering it as a queue
           printtable(table_frame,nf);
           printf("page fault\n");
           count1++;
           continue;
        }

        printtable(table_frame,nf);
		printf("\n");
    }
    printf("\nNumber of page faults : %d\n\n", count1);
}

//Function for Optimal Page Replacement Algorithm
void optimalPageReplacement()
{
    //nf-number of frames
    int n,nf,i,pos=0;

    printf("Enter number of frames\n");
    scanf("%d",&nf);
    int table_frame[nf];
    for(i=0;i<nf;i++)
    {
        table_frame[i]=-1;
    }

    printf("Enter total number of page requests\n");
    scanf("%d",&n);
    int pages[n];
    printf("Enter pages\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&pages[i]);
    }

    int count1=0;
    printf("Position of frame table after each request\n");
    for(i=0;i<n;i++)
    {
        printf("Page table after request from %2d || ",pages[i]);
        if(!present(table_frame,nf,pages[i]))
        {
             int pos = findpos(table_frame,nf,pages,i,n);
             table_frame[pos]=pages[i];


             printtable(table_frame,nf);
             printf("Page fault\n");
             count1++;
             continue;
        }
        printtable(table_frame, nf);
    }
    printf("\nNumber of page faults : %d\n\n", count1);	
}

int findpos(int table_frame[],int nf,int pages[],int curr,int np)
{
    int i, j;
    for(i=0; i<nf; i++)
    {
        if(table_frame[i] == -1)
            return i;
    }


    int pos[nf] = {0};
    for(i=0; i<nf; i++)
    {
        pos[i] = 1e9;
        for(j = curr+1; j<np; j++)
        {
            if(pages[j] == table_frame[i])
            {
                pos[i] = j;
                break;
            }
        }
    }

    int max1 = -1;
    int returnpos = -1;
	
    for(i=0; i<nf; i++)
    {
        if(pos[i] > max1)
        {
            max1 = pos[i];
            returnpos = i;
        }
    }
    return returnpos;
}

//Function for LRU Page Replacement
void LRUPageReplacement()
{
	//nf-number of frames
    int n,nf,i,pos=0;

    printf("Enter number of frames\n");
    scanf("%d",&nf);
    int table_frame[nf];
    for(i=0; i<nf; i++)
    {
        table_frame[i] = -1;
    }

    printf("Enter total number of page requests\n");
    scanf("%d", &n);
    int pages[n];
    printf("Enter pages\n");
    for(i=0;i<n;i++)
    {
        scanf("%d", &pages[i]);
    }

    int count1=0;
    printf("Position of frame table after each request\n");
    for(i=0; i<n; i++)
    {
        printf("Page table after request from %2d || ",pages[i]);
        if(!present(table_frame,nf,pages[i]))
        {
             int pos = findpos(table_frame, nf, pages, i, n);
             table_frame[pos]=pages[i];

             printtable(table_frame,nf);
             printf("Page fault\n");
             count1++;
             continue;
        }
        printtable(table_frame,nf);
		printf("\n");
    }
    printf("\nNumber of Page faults : %d\n\n", count1);
}

void LFUPageReplacement()
{
	int n, f;
	cout << "Enter the number of Pages \n";
	cin >> n;
	
	cout <<"Enter the number of frames \n";
	cin >> f;
	
	int pages[n];
	
	cout << "Enter the reference string\n";
	
	for (int i = 0 ; i < n; i++)
		cin >> pages[i];
	
	//int pages[] = {1, 2, 3, 1, 4, 5, 2, 1, 2, 6, 7, 3, 2};
    cout << "Number Of Page Faults = " << LFU(pages, n, f);
	
    getchar();
}

int LFU(int pages[], int size, int fr)
{
    // 0) Initialize Frames With '-1'
    int frames[fr];
    for (int i = 0; i < fr; i++)
        frames[i] = -1;


    int paeFaults = 0; // Count The Page Faults


    // Go Through All Pages
    for (int pageIndex = 0; pageIndex < size; pageIndex++)
    {


        // 1) Find Page In The Frames
        bool isFound = false;
        for (int i = 0; i < fr; i++)
            if (frames[i] == pages[pageIndex])
            {
                isFound = true;
                // Printing
                cout << pages[pageIndex] << endl;
                break;
            }


        // If Not Found
        if (!isFound)
        {
            // 2) Find A Free Frame
            bool hasFreeFrame = false;
            for (int i = 0; i < fr; i++)
                if (frames[i] == -1)
                {
                    hasFreeFrame = true;
                    frames[i] = pages[pageIndex];
                    paeFaults++;


                    // Printing
                    cout << pages[pageIndex] << "\t\t";
                    for (int f = 0; f < fr; f++)
                        cout << frames[f] << "\t";
                    cout << endl;


                    break;
                }


            // 3) Page Replacement (Not Found & No Free Frame)
            if (!hasFreeFrame)
            {
                // Array To Store The Used Count For Each Page In The Frames
                int countUse[fr] = {0};


                // Assign Count For Each Page In The Frames
                for (int i = 0; i < fr; i++)
                    for (int p = pageIndex; p >= 0; p--)
                        if (pages[p] == frames[i])
                            countUse[i]++;


                // Find The Victim Frame (With The Lowest Count)
                int victim = 0;
                for (int i = 0; i < fr; i++)
                    if (countUse[i] < countUse[victim])
                        victim = i;


                frames[victim] = pages[pageIndex];
                paeFaults++;


                // Printing
                cout << pages[pageIndex] << "\t\t";
                for (int f = 0; f < fr; f++)
                    cout << frames[f] << "\t";
                cout << endl;
            }
        }
    }
    return paeFaults;
}

void MFUAlgorithm()
{
	int n, f;
	cout << "Enter the number of Pages \n";
	cin >> n;
	
	cout <<"Enter the number of frames \n";
	cin >> f;
	
	int pages[n];
	
	cout << "Enter the reference string\n";
	
	for (int i = 0 ; i < n; i++)
		cin >> pages[i];
	
    cout << "Number Of Page Faults = " << MFU(pages, n, f);
	getchar();
}

int MFU(int pages[], int size, int fr)
{
    // 0) Initialize Frames With '-1'
    int frames[fr];
    for (int i = 0; i < fr; i++)
        frames[i] = -1;


    int paeFaults = 0; // Count The Page Faults


    // Go Through All Pages
    for (int pageIndex = 0; pageIndex < size; pageIndex++)
    {


        // 1) Find Page In The Frames
        bool isFound = false;
        for (int i = 0; i < fr; i++)
            if (frames[i] == pages[pageIndex])
            {
                isFound = true;
                // Printing
                cout << pages[pageIndex] << endl;
                break;
            }


        // If Not Found
        if (!isFound)
        {
            // 2) Find A Free Frame
            bool hasFreeFrame = false;
            for (int i = 0; i < fr; i++)
                if (frames[i] == -1)
                {
                    hasFreeFrame = true;
                    frames[i] = pages[pageIndex];
                    paeFaults++;


                    // Printing
                    cout << pages[pageIndex] << "\t\t";
                    for (int f = 0; f < fr; f++)
                        cout << frames[f] << "\t";
                    cout << endl;


                    break;
                }


            // 3) Page Replacement (Not Found & No Free Frame)
            if (!hasFreeFrame)
            {
                // Array To Store The Used Count For Each Page In The Frames
                int countUse[fr] = {0};


                // Assign Count For Each Page In The Frames
                for (int i = 0; i < fr; i++)
                    for (int p = pageIndex; p >= 0; p--)
                        if (pages[p] == frames[i])
                            countUse[i]++;


                // Find The Victim Frame (With The Highest Count)
                int victim = 0;
                for (int i = 0; i < fr; i++)
                    if (countUse[i] > countUse[victim])
                        victim = i;


                frames[victim] = pages[pageIndex];
                paeFaults++;


                // Printing
                cout << pages[pageIndex] << "\t\t";
                for (int f = 0; f < fr; f++)
                    cout << frames[f] << "\t";
                cout << endl;
            }
        }
    }
    return paeFaults;
}

//Function for Enhanced Second Chance Algorithm
void enhancedSecondChance()
{
	int nf;
    cout << "Enter number of frames" << endl;
    cin >> nf;
    int a[nf], rf_bit[nf];
	
    for(int i=0; i < nf; i++)
    {
        a[i] = -1;
        rf_bit[i] = 0;
    }

    int np;
    cout << "Enter number of pages" << endl;
    cin >> np;
	
    int b[np];
	
    cout << "Enter page requests" << endl;
    for(int i=0; i < np; i++)
    {
        cin >> b[i];
    }
	
    int pos = 0,count1 = 0;

    for(int i=0; i<np; i++)
    {
        printf("Page table after request from %2d || ",b[i]);
        if(!presentESA(a, nf, b[i], rf_bit))
        {
            //int pos=findpos(a,nf,b,i,np);
            pos=(pos+1)%nf;
            while(rf_bit[pos] == 1)
            {
                rf_bit[pos] = 0;
                pos = (pos+1)%nf;
            }


            a[pos] = b[i];
            printtable(a,nf);
            printf("Page fault\n");
            count1++;
            continue;
        }
		
        printtable(a, nf);
		printf("\n");
    }
     printf("\nNumber of page faults : %d\n\n", count1);
}

int presentESA(int a[],int nf,int page,int rf_bit[])
{
    for(int i=0; i < nf; i++)
    {
        if(a[i] == page)
        {
          rf_bit[i] = 1;
          return 1;
        }


    }
    return 0;
}
