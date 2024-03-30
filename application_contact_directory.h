#include "stdio.h"
#include "conio.h"
#include <stdlib.h>
#include <string.h>

enum e_control_status
{
    CONTROL_STATUS_ADD_CONTACT_DIRECTORY = 1,
    CONTROL_STATUS_DISPLAY_CONTACT_DIRECTORY,
    CONTROL_RESERACH_CONTACT_DIRECTORY,
    CONTROL_EXIT_CONTACT_DIRECTORY,
} typedef control_status_t;

enum e_error_status
{
   E_OK,
   E_NULL,
   E_REINITIALZED,
   E_NOT_INITIALZED,
   E_NO_DATA_AVAILABLE
} typedef error_status_t;

struct st_contact_directory_configuration
{
    char *p_name;
    char *p_number_phone;
    char *p_addresss;

    void *extend;            // use for extension information ex. email, facebook,etc.

    struct st_contact_directory_configuration *p_next_contact_directory;    // My idea is to use linked list to manage discrete memory area

} typedef contact_directory_configuration_t;


struct st_contact_directory_intance_ctrl
{
    contact_directory_configuration_t *current_contact_directory;
    contact_directory_configuration_t *config_contact_directory;
    control_status_t status;

    void *p_head;     // store first contact directory8
    void *p_tail;     // store last contact directory

    FILE *file;

    error_status_t ((*p_contact_directory_function[3])(struct st_contact_directory_intance_ctrl *p_ctrl));
} typedef contact_directory_intance_ctrl_t;


error_status_t initialize_data(contact_directory_intance_ctrl_t *p_ctrl, contact_directory_configuration_t *p_config);

/* Declare function */
error_status_t add_infor_into_contact_directory(contact_directory_intance_ctrl_t *p_ctrl);

error_status_t display_available_contact_directory(contact_directory_intance_ctrl_t *p_ctrl);

error_status_t research_contact_directory(contact_directory_intance_ctrl_t *p_ctrl);