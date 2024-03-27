#include "application_contact_directory.h"

static void write_alldata_to_file(contact_directory_intance_ctrl_t *p_ctrl)
{
    p_ctrl->file = freopen("assignment7.txt", "a", p_ctrl->file);
}

int initialize_data(contact_directory_intance_ctrl_t *p_ctrl, 
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
    p_ctrl->file = fopen("assignment7.txt", "w+");

    return 1; // <= should be a enum ex: STATUS_OK
}

int add_infor_into_contact_directory(contact_directory_intance_ctrl_t *p_ctrl)
{
    if(p_ctrl->p_head == NULL)
    {
        // if there is no data before, p_head = p_tail
        p_ctrl->p_head = p_ctrl->config_contact_directory;
        p_ctrl->p_tail = p_ctrl->config_contact_directory;
    }
    else
    {
        contact_directory_configuration_t *lp_next, *lp_contact_directory;
        lp_contact_directory = (contact_directory_configuration_t *)malloc(sizeof(contact_directory_configuration_t));

        // if there is data before, p_tail = current config
        p_ctrl->p_tail = lp_contact_directory;

        // old data will be next data
        lp_next = p_ctrl->config_contact_directory;
        lp_contact_directory->p_next_contact_directory = lp_next;
        p_ctrl->config_contact_directory = lp_contact_directory;
    }
    char *lp_name =  (char *)malloc(100*sizeof(char));
    printf("Enter name: ");
    scanf("%s", lp_name);
    p_ctrl->config_contact_directory->p_name = lp_name;

    char *lp_phonenum =  (char *)malloc(100*sizeof(char));
    printf("Enter phone number: ");
    scanf("%s", lp_phonenum);
    p_ctrl->config_contact_directory->p_number_phone = lp_phonenum;

    char *lp_address =  (char *)malloc(100*sizeof(char));
    printf("Enter address: ");
    scanf("%s", lp_address);
    p_ctrl->config_contact_directory->p_addresss = lp_address;

    return 1; // <= should be a enum ex: STATUS_OK
}

int display_available_contact_directory(contact_directory_intance_ctrl_t *p_ctrl)
{
    printf("Contact List:\n");
    if (p_ctrl->p_tail == NULL)
    {
        printf("There are no data available\n");
        return -1;
    }

    contact_directory_configuration_t *lp_next, *lp_contact_directory;
    lp_contact_directory = p_ctrl->p_tail;
    
    int stt = 1;
    while(lp_contact_directory!= NULL)
    {
        printf("%d.Name: %s\n", stt, lp_contact_directory->p_name);
        printf("  Phone: %s\n", lp_contact_directory->p_number_phone);
        printf("  Address: %s\n", lp_contact_directory->p_addresss);
        lp_next = lp_contact_directory->p_next_contact_directory;
        lp_contact_directory = lp_next;
        stt++;
    }
    return 1; // <= should be a enum ex: STATUS_OK
}

int research_contact_directory(contact_directory_intance_ctrl_t *p_ctrl)
{
    char search_name[100];
    printf("Enter name to search for:");
    scanf("%s", search_name);

    if (p_ctrl->p_tail == NULL)
    {
        printf("There are no data available\n");
        return -1;
    }
    contact_directory_configuration_t *lp_next, *lp_contact_directory;

    lp_contact_directory = p_ctrl->p_tail;

    int stt = 1;
    while(lp_contact_directory!= NULL)
    {
        stt = strcmp(search_name, lp_contact_directory->p_name);
        if (stt == 0) {
            break;
        }
        lp_next = lp_contact_directory->p_next_contact_directory;
        lp_contact_directory= lp_next;
    }

    if(stt == 0) // improve later if there are many same name
    {
        printf("Contact Found:\n");
        printf("Name: %s\n", lp_contact_directory->p_name);
        printf("Phone: %s\n", lp_contact_directory->p_number_phone);
        printf("Address: %s\n", lp_contact_directory->p_addresss);
    }
    else
    {
        printf("Name is not available\n");
    }
}