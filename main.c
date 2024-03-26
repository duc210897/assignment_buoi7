#include "application_contact_directory.h"

contact_directory_intance_ctrl_t apllication_control;
contact_directory_configuration_t *gp_apllication_configuration = NULL;


int main(int argc, char *argv[])
{
    initialize_data(&apllication_control, gp_apllication_configuration);

    printf("Welcome to the Contact Manager! \n 1. Add a new contact \n 2. Display all contacts \n 3. Search for a contact \n 4. Exit\n");
    
    while (1)
    {
        printf("Enter your choice: ");
        char input[2];
        scanf("%s", input);
        int num = atoi(input);
        if(num > 0 && num < 4)
        {
            apllication_control.p_contact_directory_function[num](&apllication_control);
        }
        else
        {
           printf("Goodbye!");
           break;
        }
    }
    return 0;
}
