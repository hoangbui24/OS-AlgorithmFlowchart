#include <stdio.h>
#include <stdlib.h>
static int pre_array[100];
static int page_fault[100];
static int number_page_fault = 1;

// Kiểm tra tham chiếu mới có nằm trong cột (frame) trước đó hay không
// Nếu có trả về vị trí trong frame, ngược lại trả về -1
int is_in_prearray(int page, int value)
{
    for (int i = 0; i < page; i++)
    {
        if (value == pre_array[i])
        {
            return i;
        }
    }
    return -1;
}

// In kết quả ra màn hình
void print_result(int total_page[10][100], int n, int page, int ref[100])
{
    // In chuỗi tham chiếu
    for (int i = 0; i < n; i++)
    {
        printf("%d ", ref[i]);
    }
    printf("\n");

    // In ma trận hai chiều trong quá trình thay trang
    for (int i = 0; i < page; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (total_page[i][j] != -1)
            {
                printf("%d ", total_page[i][j]);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    // In lỗi trang
    for (int i = 0; i < n; i++)
    {
        if (page_fault[i] == 1)
        {
            printf("* ");
        }
        else
        {
            printf(" ");
        }
    }
    printf("\nNumber of Page Fault: %d\n", number_page_fault);
}

// Lấy vị trí trong frame có tham chiếu ở xa nhất để thay trang mới
int farest_element(int *ref, int pivot, int page)
{
    int min = pivot;
    // Vị trí trong khung trang sẽ trả về để thay vào
    int idx;
    // Vòng lặp trong khung trang
    for (int i = 0; i < page; i++)
    {
        // Tại mỗi vị trí trong khung trang
        // Thực hiện vòng lặp từ vị trí trước đó của tham chiếu hiện tại trở về 0
        for (int j = pivot - 1; j >= 0; j--)
        {
            // Kiểm tra nếu có vị trí nào trong đó nằm trong chuỗi tham chiếutham chiếu hiện tại
            if (pre_array[i] == ref[j])
            {
                // Nếu có, kiểm tra vị trí này phải nhỏ nhơn min với min ban đầu là vị trí
                if (j < min)
                {
                    // Gán giá trị min là vị trí này
                    min = j;
                    // Giá trị trả về là khung trang thứ i
                    idx = i;
                }
                break;
            }
        }
    }

    return idx;
}

void LRU(int ref[], int n, int page)
{
    int total_page[10][100];
    int current_page = 0;
    // Tham chiếu lựa chọn là giá trị đầu tiên trong chuỗi tham chiếu, các giá trị còn lại khởi tạo là 0
    for (int i = 0; i < page; i++)
    {
        if (i == 0)
        {
            total_page[i][0] = ref[0];
        }
        else
        {
            total_page[i][0] = 0;
        }
    }

    page_fault[0] = 1;
    // Vòng lặp trên mỗi cột bắt đầu từ cột 1 để chọn tham chiếu trong chuỗi tham chiếu
    for (int j = 1; j < n; j++)
    {
        for (int i = 0; i < page; i++)
        {
            // Set giá trị cho cột j là cột trước đó
            total_page[i][j] = total_page[i][j - 1];
            // Lưu cột trước đó vào mảng pre_array
            pre_array[i] = total_page[i][j - 1];
        }

        // Kiếm tra xem tham chiếu hiện tại có nằm trong cột trước đó (mảng pre_array) hay không
        // Nếu không thì gán page_fault của tham chiếu đó là 0, nếu có thì tìm vị trí tham chiếu xa nhất trong frame và thay vào frame
        if (is_in_prearray(page, ref[j]) != -1)
        {
            page_fault[j] = 0;
        }
        else
        {
            // Nếu vị trí tham chiếu hiện tại nhỏ hơn khung trang thì tăng current_page gán tham chiếu vào frame (frame chưa được sử dụng)
            if (j < page)
            {
                current_page++;
                total_page[current_page][j] = ref[j];
            }
            else
            {
                // Lấy vị trí trong frame cần thay của tham chiếu thứ j
                int pivot = farest_element(ref, j, page);

                // Set giá trị tham chiếu vào frame
                total_page[pivot][j] = ref[j];
            }

            // Gán page_fault của tham chiếu đó là 1
            page_fault[j] = 1;

            // Tăng số lỗi trang
            number_page_fault++;
        }
    }

    // In kết quả ra màn hình
    print_result(total_page, n, page, ref);
}

int main()
{
    int page;
    int select;
    int ref[100] = {1, 9, 5, 2, 1, 2, 9, 3, 0, 0, 7};
    int n = 11;

    printf("--- Page Replacement algorithm ---\n");
    printf("1. Default referenced sequence\n");
    printf("2. Manual input sequence\n");
    scanf("%d", &select);
    switch (select)
    {
    case 1:
        break;
    case 2:
        printf("Input page: ");
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &ref[i]);
        }
    }

    printf("--- Page Replacement algorithm ---\n");
    printf("Input page frames: ");
    scanf("%d", &page);

    printf("--- Page Replacement algorithm ---\n");
    printf("1. FIFO algorithm\n");
    printf("2. OPT algorithm\n");
    printf("3. LRU algorithm\n");
    scanf("%d", &select);
    printf("--- Page Replacement algorithm ---\n");
    switch (select)
    {
    case 1:
        // Thực hiện giải thuật FIFO và in kết quả
        break;
    case 2:
        // Thực hiện giải thuật OPT và in kết quả
        break;
    case 3:
        // Thực hiện giải thuật LRU và in kết quả
        LRU(ref, n, page);
        break;
    }

    return 0;
}