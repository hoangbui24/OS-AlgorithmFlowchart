#include <iostream>
using namespace std;
static int preArray[100];
static int page_fault[100];
static int number_page_fault = 1;

int Is_in_preArray(int page, int value)
{
    for (int i = 0; i < page; i++)
    {
        if (value == preArray[i])
            return i;
    }
    return -1;
}

void Print(int total_page[10][100], int n, int page, int ref[100])
{
    // Print
    for (int i = 0; i < n; i++)
    {
        cout << ref[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < page; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (total_page[i][j] != -1)
            {
                cout << total_page[i][j] << " ";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++)
    {
        if (page_fault[i] == 1)
            cout << "* ";
        else
        {
            cout << "  ";
        }
    }
    cout << endl;
    cout << "Number of Page Fault: " << number_page_fault << endl;
}

void FIFO(int ref[], int n, int page)
{
    bool IsFault;
    int total_page[10][100];
    int current_page = 0;
    for (int i = 0; i < page; i++)
    {
        if (i == 0)
        {
            total_page[i][0] = ref[0];
        }
        else
        {
            total_page[i][0] = -1;
        }
    }
    page_fault[0] = 1;

    for (int j = 1; j < n; j++)
    {
        for (int i = 0; i < page; i++)
        {
            total_page[i][j] = total_page[i][j - 1];
            preArray[i] = total_page[i][j - 1];
        }
        if (Is_in_preArray(page, ref[j]) != -1)
        {
            page_fault[j] = -1;
        }
        else
        {
            current_page++;
            if (current_page == page)
                current_page = 0;
            total_page[current_page][j] = ref[j];
            page_fault[j] = 1;
            number_page_fault++;
        }
    }
    Print(total_page, n, page, ref);
}

int main()
{
    int page;
    int temp;
    int ref[11] = {2, 0, 5, 2, 1, 0, 4, 7, 0, 0, 7};
    ;
    int n = 11;
    cout << "--- FIFO Page Replacement algorithm ---" << endl;
    cout << "1. Default referenced sequence" << endl;
    cout << "2. Manual input sequence" << endl;
    cin >> temp;
    switch (temp)
    {
    case 1:

        break;
    case 2:
        cout << "Enter the number of pages: ";
        cin >> n;
        cout << "Enter referenced sequence values: " << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "No [" << i + 1 << "]: ";
            cin >> ref[i];
        }
    }

    cout << "--- FIFO Page Replacement algorithm ---" << endl;
    cout << "Input page frames: ";
    cin >> page;
    cout << "--- FIFO Page Replacement algorithm--- " << endl;
    FIFO(ref, n, page);
    system("pause");
    return 0;
}
