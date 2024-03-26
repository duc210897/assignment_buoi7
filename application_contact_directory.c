#include "application_contact_directory.h"

void initialize_data(contact_directory_intance_ctrl_t *p_ctrl, 
                                 contact_directory_configuration_t *p_config)
{
    p_ctrl->p_head = NULL;
    p_ctrl->p_tail = NULL;

    p_ctrl->p_contact_directory_function[CONTROL_STATUS_ADD_CONTACT_DIRECTORY] =  add_infor_into_contact_directory;
    p_ctrl->p_contact_directory_function[CONTROL_STATUS_DISPLAY_CONTACT_DIRECTORY] =  display_available_contact_directory;
    p_ctrl->p_contact_directory_function[CONTROL_RESERACH_CONTACT_DIRECTORY] =  research_contact_directory;

    if(p_config == NULL)
    {
        p_config = (contact_directory_configuration_t *)malloc(sizeof(contact_directory_configuration_t));
    }
    p_config->extend = NULL;
    p_config->p_next_contact_directory = NULL;
    p_ctrl->config_contact_directory  = p_config;
    p_ctrl->current_contact_directory = p_config;
}

void add_infor_into_contact_directory(contact_directory_intance_ctrl_t *p_ctrl)
{
    if(p_ctrl->p_head == NULL)
    {
        // if there is no data before, p_head = p_tail
        p_ctrl->p_head = p_ctrl->config_contact_directory;
        p_ctrl->p_tail = p_ctrl->config_contact_directory;
    }
    else if(p_ctrl->current_contact_directory == p_ctrl->p_tail)
    {
         p_ctrl->config_contact_directory =  (contact_directory_configuration_t *)malloc(sizeof(contact_directory_configuration_t));

        // if there is data before, p_tail = current config
        p_ctrl->p_tail = p_ctrl->config_contact_directory;

        // old data will be next data
        contact_directory_configuration_t *p_next = p_ctrl->current_contact_directory;
        p_ctrl->config_contact_directory->p_next_contact_directory = p_next;

        // new data will be current data
        p_ctrl->current_contact_directory = p_ctrl->config_contact_directory;
    }
    else
    {
        // improve later
    }
    char *lp_name =  (char *)malloc(100*sizeof(char));
    printf("Enter name: ");
    scanf("%s", lp_name);
    p_ctrl->current_contact_directory->p_name = lp_name;

    char *lp_phonenum =  (char *)malloc(100*sizeof(char));
    printf("Enter phone number: ");
    scanf("%s", lp_phonenum);
    p_ctrl->current_contact_directory->p_number_phone = lp_phonenum;

    char *lp_address =  (char *)malloc(100*sizeof(char));
    printf("Enter address: ");
    scanf("%s", lp_address);
    p_ctrl->current_contact_directory->p_addresss = lp_address;

}

void display_available_contact_directory(contact_directory_intance_ctrl_t *p_ctrl)
{
    printf("Contact List:\n");
    p_ctrl->current_contact_directory = p_ctrl->p_tail;
    if (p_ctrl->current_contact_directory == NULL)
    {
        printf("There are no data available");
    }
    
    int stt = 1;
    while(p_ctrl->current_contact_directory != NULL)
    {
        printf("%d.Name: %s\n", stt, p_ctrl->current_contact_directory->p_name);
        printf("  Phone: %s\n", p_ctrl->current_contact_directory->p_number_phone);
        printf("  Address: %s\n", p_ctrl->current_contact_directory->p_addresss);
        contact_directory_configuration_t *p_next = p_ctrl->current_contact_directory->p_next_contact_directory;
        p_ctrl->current_contact_directory = p_next;
        stt++;
    }
    /* Retore value */
    p_ctrl->current_contact_directory = p_ctrl->p_tail;
}

void research_contact_directory(contact_directory_intance_ctrl_t *p_ctrl)
{
    char search_name[100];
    printf("Enter name to search for:");
    scanf("%s", search_name);
    
    p_ctrl->current_contact_directory = p_ctrl->p_tail;
    if (p_ctrl->current_contact_directory == NULL)
    {
        printf("There are no data available");
    }
    int stt = 1;
    while(p_ctrl->current_contact_directory != NULL)
    {
        stt = strcmp(search_name, p_ctrl->current_contact_directory->p_name);
        if (stt == 0) {
            break;
        }
        contact_directory_configuration_t *p_next = p_ctrl->current_contact_directory->p_next_contact_directory;
        p_ctrl->current_contact_directory = p_next;
    }

    if(stt == 0) // improve later if there are many same name
    {
        printf("Contact Found:\n");
        printf("Name: %s\n", p_ctrl->current_contact_directory->p_name);
        printf("Phone: %s\n", p_ctrl->current_contact_directory->p_number_phone);
        printf("Address: %s\n", p_ctrl->current_contact_directory->p_addresss);
    }
    else
    {
        printf("Name is not available");
    }

    /* Retore value */
    p_ctrl->current_contact_directory = p_ctrl->p_tail;
}