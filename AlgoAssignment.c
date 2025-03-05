#include <stdio.h>
#include <stdlib.h>

#define SIZE 4
#define logs 5
#define total_logs 20


// date/time structure 
struct dhm
{
    int day;
    int hour;
    int minute;
};

/// issues structure
struct issues
{
    int issue_code;
    char issue_decs[100];
};

/// resolution structure
struct resolution
{
    int resolution_code;
    char resolution_desc[100];
};


/// structure for data in production line
struct production_line
{
    int line_code;
    int batch_code;
    struct dhm date_time;
    int product_id;
    struct issues issue_code_desc;
    struct resolution resolution_code_desc;
    int rep_employee_id;
};

struct summary
{
    int product_id;
    int issues;
};

/// function to enter data into structure
void test_data(struct production_line array[SIZE][logs]);

///merge sort functions
void merge_sort(struct production_line *line, int length);
void merge_sort_recursion(struct production_line *line, int l, int r);
void merge_sorted_arrays(struct production_line *line, int l, int m, int r);

/// Merge four sorted arrays 
int* merge_four_sorted_arrays(struct production_line *line1, int size1, struct production_line *line2, int size2, struct production_line *line3, int size3, struct production_line *line4, int size4);
int* merge_sorted_arrays_task2(struct production_line *line1, int size1, struct production_line *line2, int size2);

/// searching for the issue code and product id
void search_for_issue(struct production_line *merged_result, int, int);

///
void summaryIssue(struct production_line *merged_result);


int main(){
    ///inittializing 2-D array of structures 
    struct production_line line[SIZE][logs];

    ///calling upon function to add data to structure
    test_data(line);


    ///length variable contains amount of logs
    int length = logs;

    /// Task 1
    ///for loop to enter enter the 4 lines logs to sort and print them 
    printf("Task 1, sorting the logs on all 4 lines\n");
    for(int i = 0; i < SIZE; i++){
        ///entering what line is to be sorted and the amount of logs into function
        merge_sort(line[i], length);

        ///print statement displaying what lines logs are being displayed
        printf("\nSorted Logs for Line %d\n", i + 1);
		
		for (int j = 0; j < 5; j++) 
		{
			/// printing the report for task 1
			struct production_line log = line[i][j];
			
			printf("Product ID-> %d, Issue Code-> %d, Date-> %02d-%02d-%02d\n", log.product_id, log.issue_code_desc.issue_code,
			log.date_time.day, log.date_time.hour, log.date_time.minute);
		}
    }

    /// Task 2
    
    
    struct production_line *merged_result = merge_four_sorted_arrays(line[0], logs, line[1], logs, line[2], logs, line[3], logs);


    printf("\nTask 2, merged sorted lines\n");

    // Print the merged result
    for (int i = 0; i < logs + logs + logs + logs; i++) {
        printf("Product ID-> %d, Issue Code-> %d, Line Code->%d\n", merged_result[i].product_id, merged_result[i].issue_code_desc.issue_code, merged_result[i].line_code);
    }
    printf("\n");

    // Free dynamically allocated memory
    ///free(merged_result);

    
    ///Task 3
    ///showing the user the product ids and issue codes to pick from
    printf("\nTask 3, Searching for earliest occurence of an issue code\n");
    printf("These are all the Product ID and Issue Code\n");
    for(int i = 0; i < 20; i++){
        printf("Product ID-> %d, Issue Code-> %d\n", merged_result[i].product_id, merged_result[i].issue_code_desc.issue_code);
        }

    int user_prod_id;
    int user_issue_code;

    ///ask the user to enter a product id and issue code to search for
    printf("Choose a Product ID \n");
    scanf("%d", &user_prod_id);
    printf("Choose a Issue Code\n");
    scanf("%d", &user_issue_code);

    ///entering sorted array, and users entries
    search_for_issue(merged_result, user_prod_id, user_issue_code);

    ///Task 4

    summaryIssue(merged_result);

    /// Free dynamically allocated memory
    free(merged_result);
    
    return 0;


}

/// Task 1
void test_data(struct production_line line[SIZE][logs]){

    ///line 1
    line[0][0] = (struct production_line) {1, 1001, {01, 17, 8}, 10001, {601, "Wrong Label"}, {701, "Replace label"}, 401};
    line[0][1] = (struct production_line) {1, 1002, {01, 18, 10}, 10001, {602, "Packing Error"}, {702, "Repack"}, 401};
    line[0][2] = (struct production_line) {1, 1003, {02, 12, 32}, 10002, {603, "Package Tear"}, {703, "Replace package"}, 402};
    line[0][3] = (struct production_line) {1, 1004, {03, 10, 45}, 10003, {604, "Faulty Equipment"}, {704, "Replace Equipment"}, 403};
    line[0][4] = (struct production_line) {1, 1005, {04, 11, 23}, 10004, {605, "Package Leaking"}, {705, "Seal Leak"}, 404};

    ///line 2
    line[1][0] = (struct production_line) {2, 2001, {05, 16, 18}, 20001, {601, "Wrong Label"}, {701, "Replace label"}, 405};
    line[1][1] = (struct production_line) {2, 2002, {06, 17, 17}, 20002, {606, "Missing Part"}, {706, "Replace Part"}, 406};
    line[1][2] = (struct production_line) {2, 2003, {07, 15, 14}, 20003, {607, "Missing Ingredient"}, {707, "Replace Ingredient"}, 407};
    line[1][3] = (struct production_line) {2, 2004, {8, 9, 30}, 20004, {608, "Missing Label"}, {708, "Add Label"}, 408};
    line[1][4] = (struct production_line) {2, 2005, {9, 18, 25}, 20005, {609, "Underfilled"}, {709, "Amount Adjusted"}, 409};

    ///line 3
    line[2][0] = (struct production_line) {3, 3001, {14, 13, 39}, 30001, {603, "Package Tear"}, {703, "Replace Package"}, 409};
    line[2][1] = (struct production_line) {3, 3002, {15, 12, 43}, 30002, {610, "Incorrect Ingredient"}, {710, "Ingrediant Added"}, 408};
    line[2][2] = (struct production_line) {3, 3003, {16, 20, 21}, 30002, {605, "Package Leaking"}, {705, "Seal Leak"}, 407};
    line[2][3] = (struct production_line) {3, 3004, {17, 4, 50}, 30003, {609, "Underfilled"}, {709, "Amount Adjusted"}, 406};
    line[2][4] = (struct production_line) {3, 3005, {18, 3, 13}, 30004, {603, "Package Tear"}, {703, "Replace Package"}, 405};

    ///line 4
    line[3][0] = (struct production_line) {4, 4001, {10, 17, 3}, 40001, {606, "Missing Part"}, {706, "Replace part"}, 410};
    line[3][1] = (struct production_line) {4, 4002, {11, 24, 14}, 40002, {604, "Faulty Equipment"}, {704, "Replace Equipment"}, 411};
    line[3][2] = (struct production_line) {4, 4003, {12, 50, 50}, 40003, {606, "Missing Part"}, {706, "Replace part"}, 412};
    line[3][3] = (struct production_line) {4, 4004, {13, 1, 3}, 40004, {602, "Packing Error"}, {702, "Repack"}, 413};
    line[3][4] = (struct production_line) {4, 4005, {14, 37, 7}, 40005, {608, "Missing Label"}, {708, "Add Label"}, 414};
}

///Task 1

int compare(struct production_line *line_1, struct production_line *line_2){

    ///comparing if product id is not equal
    if ((*line_1).product_id != (*line_2).product_id){
        ///return difference
        return (*line_1).product_id - (*line_2).product_id;
    }

    ///comparing if issue code is not equal
    else if ((*line_1).issue_code_desc.issue_code != (*line_2).issue_code_desc.issue_code){
        ///return difference
        return (*line_1).issue_code_desc.issue_code - (*line_2).issue_code_desc.issue_code;
    }

    ///comparing if date_time.day is not equal
    else if ((*line_1).date_time.day != (*line_2).date_time.day){
        ///return difference
        return (*line_1).date_time.day - (*line_2).date_time.day;
    }

    ///comparing if date_time.hour is not equal
    else if ((*line_1).date_time.hour != (*line_2).date_time.hour){
        ///return difference
        return (*line_1).date_time.hour - (*line_2).date_time.hour;
    }

    ///comparing if date_time.minute is not equal
    else if ((*line_1).date_time.minute != (*line_2).date_time.minute){
        ///return difference
        return (*line_1).date_time.minute - (*line_2).date_time.minute;
    }

    ///all entries equal return 0
    return 0;

}

/// merge_sort function to make code simpler all it does is call the merge_sort_recursion function 
void merge_sort(struct production_line *line, int length){

    ///passing the array, 0 and length - 1 are the left and right most points of the array
    merge_sort_recursion(line, 0, length - 1);

}

void merge_sort_recursion(struct production_line *line, int l, int r){
    
    ///recursion stops when l is greater or equal to r
    if (l < r){
        /// middle point of the array
        int m = l + (r-l) / 2;

        ///recalling the function and passing the left side of the array
        merge_sort_recursion(line, l, m);
        ///recalling the function and passing the right side of the array
        merge_sort_recursion(line, m+1, r);

        ///merging the sorted portions of the array in this function
        merge_sorted_arrays(line, l, m , r);
        }
}


void merge_sorted_arrays(struct production_line *line, int l, int m, int r){
    
    ///length of each side of the array
    int left_side = m - l + 1;
	int right_side = r - m;

    ///creating two temp arrays and copying the left and right portions into them
	struct production_line left_arr[left_side], right_arr[right_side];

	///Copying the left side data into temp array
	for(int i = 0; i < left_side; i++){
        left_arr[i] = line[l + i];
    }

	///Copying the right side data into a temp array
	for(int i = 0; i < right_side; i++){
        right_arr[i] = line[m + 1 + i];
    }

	// Left and right pointers, index for the merged array
	int left = 0, right = 0, index = l;

	// Merge the two arrays based on product_id.
	while(left < left_side && right < right_side)
	{
		// If the function returns a negative number, the left value is smaller 
		if (compare(&left_arr[left], &right_arr[right]) <= 0){
            line[index++] = left_arr[left++];
            }
			
		// Else the right is the smaller value
		else{
            line[index++] = right_arr[right++];
            }
	}

	// Assigning left over variables
	while(left < left_side){
        line[index++] = left_arr[left++];
    }
	while(right < right_side){
        line[index++] = right_arr[right++];
    }

}


///Task 2

int* merge_sorted_arrays_task2(struct production_line *line1, int size1, struct production_line *line2, int size2) {
    ///array created to store all the merged arrays
    struct production_line *merged_array = malloc((size1 + size2) * sizeof(struct production_line));

    ///using the code from the previous task to compare and merging the arrays
    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2) {
        if (compare(&line1[i], &line2[j]) <= 0) {
            merged_array[k++] = line1[i++];
        } else {
            merged_array[k++] = line2[j++];
        }
    }

    while (i < size1) {
        merged_array[k++] = line1[i++];
    }

    while (j < size2) {
        merged_array[k++] = line2[j++];
    }

    return merged_array;
}


int* merge_four_sorted_arrays(struct production_line *line1, int size1, struct production_line *line2, int size2, struct production_line *line3, int size3, struct production_line *line4, int size4) {
    ///Merging the first two arrays
    int *merged1 = merge_sorted_arrays_task2(line1, size1, line2, size2);
    ///Merging third array with the result of merged1(the array1 and array2 merged)
    int *merged2 = merge_sorted_arrays_task2(merged1, size1 + size2, line3, size3);
    ///Merging the fourth array with the result of merged2(the array1, array2 and array3 merged)
    int *merged_result = merge_sorted_arrays_task2(merged2, size1 + size2 + size3, line4, size4);

    ///Free memory allocated for temporary merged arrays
    free(merged1);
    free(merged2);

    return merged_result;
}


///Task 3

void search_for_issue(struct production_line *merged_result, int user_prod_id, int user_issue_code){
    
    int earliestIndex = total_logs; // Initialize earliest index to the maximum value

    //loop through each production line's sorted logs
    
    int left = 0;
    int right = total_logs - 1;

    //Binary search the sorted logs of the current production line
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (merged_result[mid].product_id == user_prod_id) {
            if (merged_result[mid].issue_code_desc.issue_code == user_issue_code){
                // Record the index of the earliest occurrence
                if (mid < earliestIndex)
                earliestIndex = mid;
            }

            // Continue searching for earlier occurrences
            right = mid - 1;
        } 
        else if (merged_result[mid].product_id < user_prod_id) {
            left = mid + 1;
        } 
        else {
            right = mid - 1;
        }
    }
    

    // Output the result
    if (earliestIndex < total_logs) {
        printf("Earliest occurrence: Product ID: %d, Line Code: %d, Issue Code: %d\n",
               merged_result[earliestIndex].product_id,
               merged_result[earliestIndex].line_code,
               merged_result[earliestIndex].issue_code_desc.issue_code);
    } else {
        printf("That issue code wasn't found with that Product ID\n");
    }
}


///task 4

void summaryIssue(struct production_line *merged_result){

    ///variable count amount of issues
    int issue_count;

    
    if (issue_count == 0){
        printf("No issues found.\n");
        return;
    }

	///Initializing summary for the first product
	struct summary summaries[total_logs]; 

	int summary_index = 0;

	///Assigning first product to the summary
	summaries[0].product_id = merged_result[0].product_id;

	summaries[0].issues = 1;

    ///iterates through the merged result to create summaries
	for (int i = 1; i < issue_count; i++) 
	{
		///If unique, put it in the next slot in the summary
		if (merged_result[i].product_id != merged_result[i-1].product_id) 
		{
			///next summary entry for a new product
			summary_index++;

			///Assign the new product to summary
			summaries[summary_index].product_id = merged_result[i].product_id;
			summaries[summary_index].issues= 1;
		} 
		///else it already exists increase the issue count for that product
		else{
            summaries[summary_index].issues++;
        }

	}


	///Printing
    printf("\nTask 4, Report of summary of all issues\n");
	for (int i = 0; i <= summary_index; i++){
        printf("Product ID-> %d, Issue Count-> %d\n", summaries[i].product_id, summaries[i].issues);
    }

    
}

