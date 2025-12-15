#include <stdio.h>
#include <stdlib.h> 

#define BUFFER_SIZE 256 

int main() {
    
    char input_buffer[BUFFER_SIZE];
    char* final_string = NULL; 
    int current_len = 0;    

    printf("--- Dynamic Concatenation (Pointers & Only INT) ---\n");
    printf("Enter strings to concatenate. Enter 'Q' to stop.\n");

    while (1) {
        printf("Enter string (or 'Q'): ");
        
        if (fgets(input_buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }
        
        
        int input_len = 0;
        char* temp_ptr = input_buffer; 
        while (*temp_ptr != '\0') {
            input_len++;
            temp_ptr++;
        }
        
        
        if (input_len > 0 && input_buffer[input_len - 1] == '\n') {
            input_buffer[input_len - 1] = '\0';
            input_len--;
        }

        
        if (input_len == 1 && input_buffer[0] == 'Q') {
            break;
        }

        
        if (input_len == 0) {
            printf("Empty string entered, skipping.\n");
            continue;
        }

        
        
        int new_total_len = current_len + input_len + 1; 
        
        
        char* new_mem_ptr = (char*)realloc(final_string, (size_t)new_total_len * sizeof(char));
        
        if (new_mem_ptr == NULL) {
            fprintf(stderr, "Memory reallocation failed.\n");
            goto cleanup; 
        }
        
        final_string = new_mem_ptr;
      
        
        char* dest_ptr = final_string + current_len; 
        char* src_ptr = input_buffer;
        
        while (*src_ptr != '\0') {
            *dest_ptr = *src_ptr;
            dest_ptr++;
            src_ptr++;
        }
        
        *dest_ptr = '\0';
        
        current_len = current_len + input_len;

        printf("Current Concatenated String: %s\n", final_string);
    }
  
    if (final_string != NULL) {
        printf("\n--- Final Result ---\n");
        printf("Final Concatenated String: %s\n", final_string);
    } else {
        printf("\nNo strings entered.\n");
    }

cleanup:
    if (final_string != NULL) {
        free(final_string);
        printf("Memory freed.\n");
    }
    
    return 0;
}
