
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// main menu (hub) for application
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i = 0;
    if (patient != NULL)
    {
        displayPatientTableHeader();
        for (i = 0; i < max; i++)
        {
            if (patient[i].patientNumber != 0)
            {
                displayPatientData(patient + i, fmt);
            }
        }
    }
    else
        printf("*** No records found ***");
    putchar('\n');
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int input = 1;
    while (input)
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        input = inputIntRange(0, 2);
        putchar('\n');
        if (input == 1)
        {
            searchPatientByPatientNumber(patient, max);
        }
        else if (input == 2)
        {
            searchPatientByPhoneNumber(patient, max);
        }
        if (input != 0)
        {
            putchar('\n');
            suspend();
        }
    }
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i, sizeofstruct = 0, index;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            sizeofstruct++;
        }
        if (patient[i].patientNumber == 0)
        {
            index = i;
        }
    }
    if (max > sizeofstruct)
    {
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(patient + index);
        printf("*** New patient record added ***\n\n");
    }
    else
        printf("ERROR: Patient listing is FULL!\n\n");
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int exist, patientnumber;
    printf("Enter the patient number: ");
    scanf("%d", &patientnumber);
    putchar('\n');
    exist = findPatientIndexByPatientNum(patientnumber, patient, max);
    if (exist + 1)
    {
        menuPatientEdit(patient + exist);
    }
    else
        printf("ERROR: Patient record not found!\n");
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int exist, patientnumber;
    char decision;
    printf("Enter the patient number: ");
    scanf("%d", &patientnumber);
    clearInputBuffer();
    exist = findPatientIndexByPatientNum(patientnumber, patient, max);
    if (exist + 1)
    {
        putchar('\n');
        displayPatientData(patient + exist, FMT_FORM);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        decision = inputCharOption("yn");
        if (decision == 'y')
        {
            patient[exist].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
        else
            printf("Operation aborted.\n\n");
    }
    else
        printf("\nERROR: Patient record not found!\n\n");
}

// View ALL scheduled appointments
void viewAllAppointments(const struct ClinicData* clinicdata)
{
    int i, j;
    displayScheduleTableHeader(&clinicdata->appointments->date, 1);
    for (j = 0; j < clinicdata->maxAppointments - 1; j++)
    {
        for (i = 0; i < clinicdata->maxAppointments - 1 - j; i++)
        {
            if (clinicdata->appointments[i].date.year > clinicdata->appointments[i + 1].date.year)
            {
                clinicdata->appointments[i].date.year = clinicdata->appointments[i].date.year + clinicdata->appointments[i + 1].date.year;
                clinicdata->appointments[i + 1].date.year = clinicdata->appointments[i].date.year - clinicdata->appointments[i + 1].date.year;
                clinicdata->appointments[i].date.year = clinicdata->appointments[i].date.year - clinicdata->appointments[i + 1].date.year;
                clinicdata->appointments[i].date.month = clinicdata->appointments[i].date.month + clinicdata->appointments[i + 1].date.month;
                clinicdata->appointments[i + 1].date.month = clinicdata->appointments[i].date.month - clinicdata->appointments[i + 1].date.month;
                clinicdata->appointments[i].date.month = clinicdata->appointments[i].date.month - clinicdata->appointments[i + 1].date.month;
                clinicdata->appointments[i].date.day = clinicdata->appointments[i].date.day + clinicdata->appointments[i + 1].date.day;
                clinicdata->appointments[i + 1].date.day = clinicdata->appointments[i].date.day - clinicdata->appointments[i + 1].date.day;
                clinicdata->appointments[i].date.day = clinicdata->appointments[i].date.day - clinicdata->appointments[i + 1].date.day;
                clinicdata->appointments[i].time.hour = clinicdata->appointments[i].time.hour + clinicdata->appointments[i + 1].time.hour;
                clinicdata->appointments[i + 1].time.hour = clinicdata->appointments[i].time.hour - clinicdata->appointments[i + 1].time.hour;
                clinicdata->appointments[i].time.hour = clinicdata->appointments[i].time.hour - clinicdata->appointments[i + 1].time.hour;
                clinicdata->appointments[i].time.min = clinicdata->appointments[i].time.min + clinicdata->appointments[i + 1].time.min;
                clinicdata->appointments[i + 1].time.min = clinicdata->appointments[i].time.min - clinicdata->appointments[i + 1].time.min;
                clinicdata->appointments[i].time.min = clinicdata->appointments[i].time.min - clinicdata->appointments[i + 1].time.min;
                clinicdata->appointments[i].Patientnumber = clinicdata->appointments[i].Patientnumber + clinicdata->appointments[i + 1].Patientnumber;
                clinicdata->appointments[i + 1].Patientnumber = clinicdata->appointments[i].Patientnumber - clinicdata->appointments[i + 1].Patientnumber;
                clinicdata->appointments[i].Patientnumber = clinicdata->appointments[i].Patientnumber - clinicdata->appointments[i + 1].Patientnumber;
            }
            else if (clinicdata->appointments[i].date.year == clinicdata->appointments[i + 1].date.year)
            {
                if (clinicdata->appointments[i].date.month > clinicdata->appointments[i + 1].date.month)
                {
                    clinicdata->appointments[i].date.year = clinicdata->appointments[i].date.year + clinicdata->appointments[i + 1].date.year;
                    clinicdata->appointments[i + 1].date.year = clinicdata->appointments[i].date.year - clinicdata->appointments[i + 1].date.year;
                    clinicdata->appointments[i].date.year = clinicdata->appointments[i].date.year - clinicdata->appointments[i + 1].date.year;
                    clinicdata->appointments[i].date.month = clinicdata->appointments[i].date.month + clinicdata->appointments[i + 1].date.month;
                    clinicdata->appointments[i + 1].date.month = clinicdata->appointments[i].date.month - clinicdata->appointments[i + 1].date.month;
                    clinicdata->appointments[i].date.month = clinicdata->appointments[i].date.month - clinicdata->appointments[i + 1].date.month;
                    clinicdata->appointments[i].date.day = clinicdata->appointments[i].date.day + clinicdata->appointments[i + 1].date.day;
                    clinicdata->appointments[i + 1].date.day = clinicdata->appointments[i].date.day - clinicdata->appointments[i + 1].date.day;
                    clinicdata->appointments[i].date.day = clinicdata->appointments[i].date.day - clinicdata->appointments[i + 1].date.day;
                    clinicdata->appointments[i].time.hour = clinicdata->appointments[i].time.hour + clinicdata->appointments[i + 1].time.hour;
                    clinicdata->appointments[i + 1].time.hour = clinicdata->appointments[i].time.hour - clinicdata->appointments[i + 1].time.hour;
                    clinicdata->appointments[i].time.hour = clinicdata->appointments[i].time.hour - clinicdata->appointments[i + 1].time.hour;
                    clinicdata->appointments[i].time.min = clinicdata->appointments[i].time.min + clinicdata->appointments[i + 1].time.min;
                    clinicdata->appointments[i + 1].time.min = clinicdata->appointments[i].time.min - clinicdata->appointments[i + 1].time.min;
                    clinicdata->appointments[i].time.min = clinicdata->appointments[i].time.min - clinicdata->appointments[i + 1].time.min;
                    clinicdata->appointments[i].Patientnumber = clinicdata->appointments[i].Patientnumber + clinicdata->appointments[i + 1].Patientnumber;
                    clinicdata->appointments[i + 1].Patientnumber = clinicdata->appointments[i].Patientnumber - clinicdata->appointments[i + 1].Patientnumber;
                    clinicdata->appointments[i].Patientnumber = clinicdata->appointments[i].Patientnumber - clinicdata->appointments[i + 1].Patientnumber;
                }
                else if (clinicdata->appointments[i].date.month == clinicdata->appointments[i + 1].date.month)
                {
                    if (clinicdata->appointments[i].date.day > clinicdata->appointments[i + 1].date.day)
                    {
                        clinicdata->appointments[i].date.year = clinicdata->appointments[i].date.year + clinicdata->appointments[i + 1].date.year;
                        clinicdata->appointments[i + 1].date.year = clinicdata->appointments[i].date.year - clinicdata->appointments[i + 1].date.year;
                        clinicdata->appointments[i].date.year = clinicdata->appointments[i].date.year - clinicdata->appointments[i + 1].date.year;
                        clinicdata->appointments[i].date.month = clinicdata->appointments[i].date.month + clinicdata->appointments[i + 1].date.month;
                        clinicdata->appointments[i + 1].date.month = clinicdata->appointments[i].date.month - clinicdata->appointments[i + 1].date.month;
                        clinicdata->appointments[i].date.month = clinicdata->appointments[i].date.month - clinicdata->appointments[i + 1].date.month;
                        clinicdata->appointments[i].date.day = clinicdata->appointments[i].date.day + clinicdata->appointments[i + 1].date.day;
                        clinicdata->appointments[i + 1].date.day = clinicdata->appointments[i].date.day - clinicdata->appointments[i + 1].date.day;
                        clinicdata->appointments[i].date.day = clinicdata->appointments[i].date.day - clinicdata->appointments[i + 1].date.day;
                        clinicdata->appointments[i].time.hour = clinicdata->appointments[i].time.hour + clinicdata->appointments[i + 1].time.hour;
                        clinicdata->appointments[i + 1].time.hour = clinicdata->appointments[i].time.hour - clinicdata->appointments[i + 1].time.hour;
                        clinicdata->appointments[i].time.hour = clinicdata->appointments[i].time.hour - clinicdata->appointments[i + 1].time.hour;
                        clinicdata->appointments[i].time.min = clinicdata->appointments[i].time.min + clinicdata->appointments[i + 1].time.min;
                        clinicdata->appointments[i + 1].time.min = clinicdata->appointments[i].time.min - clinicdata->appointments[i + 1].time.min;
                        clinicdata->appointments[i].time.min = clinicdata->appointments[i].time.min - clinicdata->appointments[i + 1].time.min;
                        clinicdata->appointments[i].Patientnumber = clinicdata->appointments[i].Patientnumber + clinicdata->appointments[i + 1].Patientnumber;
                        clinicdata->appointments[i + 1].Patientnumber = clinicdata->appointments[i].Patientnumber - clinicdata->appointments[i + 1].Patientnumber;
                        clinicdata->appointments[i].Patientnumber = clinicdata->appointments[i].Patientnumber - clinicdata->appointments[i + 1].Patientnumber;
                    }
                    else if (clinicdata->appointments[i].date.day == clinicdata->appointments[i + 1].date.day)
                    {
                        if (clinicdata->appointments[i].time.hour > clinicdata->appointments[i + 1].time.hour)
                        {
                            clinicdata->appointments[i].date.year = clinicdata->appointments[i].date.year + clinicdata->appointments[i + 1].date.year;
                            clinicdata->appointments[i + 1].date.year = clinicdata->appointments[i].date.year - clinicdata->appointments[i + 1].date.year;
                            clinicdata->appointments[i].date.year = clinicdata->appointments[i].date.year - clinicdata->appointments[i + 1].date.year;
                            clinicdata->appointments[i].date.month = clinicdata->appointments[i].date.month + clinicdata->appointments[i + 1].date.month;
                            clinicdata->appointments[i + 1].date.month = clinicdata->appointments[i].date.month - clinicdata->appointments[i + 1].date.month;
                            clinicdata->appointments[i].date.month = clinicdata->appointments[i].date.month - clinicdata->appointments[i + 1].date.month;
                            clinicdata->appointments[i].date.day = clinicdata->appointments[i].date.day + clinicdata->appointments[i + 1].date.day;
                            clinicdata->appointments[i + 1].date.day = clinicdata->appointments[i].date.day - clinicdata->appointments[i + 1].date.day;
                            clinicdata->appointments[i].date.day = clinicdata->appointments[i].date.day - clinicdata->appointments[i + 1].date.day;
                            clinicdata->appointments[i].time.hour = clinicdata->appointments[i].time.hour + clinicdata->appointments[i + 1].time.hour;
                            clinicdata->appointments[i + 1].time.hour = clinicdata->appointments[i].time.hour - clinicdata->appointments[i + 1].time.hour;
                            clinicdata->appointments[i].time.hour = clinicdata->appointments[i].time.hour - clinicdata->appointments[i + 1].time.hour;
                            clinicdata->appointments[i].time.min = clinicdata->appointments[i].time.min + clinicdata->appointments[i + 1].time.min;
                            clinicdata->appointments[i + 1].time.min = clinicdata->appointments[i].time.min - clinicdata->appointments[i + 1].time.min;
                            clinicdata->appointments[i].time.min = clinicdata->appointments[i].time.min - clinicdata->appointments[i + 1].time.min;
                            clinicdata->appointments[i].Patientnumber = clinicdata->appointments[i].Patientnumber + clinicdata->appointments[i + 1].Patientnumber;
                            clinicdata->appointments[i + 1].Patientnumber = clinicdata->appointments[i].Patientnumber - clinicdata->appointments[i + 1].Patientnumber;
                            clinicdata->appointments[i].Patientnumber = clinicdata->appointments[i].Patientnumber - clinicdata->appointments[i + 1].Patientnumber;
                        }
                        else if (clinicdata->appointments[i].time.hour == clinicdata->appointments[i + 1].time.hour)
                        {
                            if (clinicdata->appointments[i].time.min > clinicdata->appointments[i + 1].time.min)
                            {
                                clinicdata->appointments[i].date.year = clinicdata->appointments[i].date.year + clinicdata->appointments[i + 1].date.year;
                                clinicdata->appointments[i + 1].date.year = clinicdata->appointments[i].date.year - clinicdata->appointments[i + 1].date.year;
                                clinicdata->appointments[i].date.year = clinicdata->appointments[i].date.year - clinicdata->appointments[i + 1].date.year;
                                clinicdata->appointments[i].date.month = clinicdata->appointments[i].date.month + clinicdata->appointments[i + 1].date.month;
                                clinicdata->appointments[i + 1].date.month = clinicdata->appointments[i].date.month - clinicdata->appointments[i + 1].date.month;
                                clinicdata->appointments[i].date.month = clinicdata->appointments[i].date.month - clinicdata->appointments[i + 1].date.month;
                                clinicdata->appointments[i].date.day = clinicdata->appointments[i].date.day + clinicdata->appointments[i + 1].date.day;
                                clinicdata->appointments[i + 1].date.day = clinicdata->appointments[i].date.day - clinicdata->appointments[i + 1].date.day;
                                clinicdata->appointments[i].date.day = clinicdata->appointments[i].date.day - clinicdata->appointments[i + 1].date.day;
                                clinicdata->appointments[i].time.hour = clinicdata->appointments[i].time.hour + clinicdata->appointments[i + 1].time.hour;
                                clinicdata->appointments[i + 1].time.hour = clinicdata->appointments[i].time.hour - clinicdata->appointments[i + 1].time.hour;
                                clinicdata->appointments[i].time.hour = clinicdata->appointments[i].time.hour - clinicdata->appointments[i + 1].time.hour;
                                clinicdata->appointments[i].time.min = clinicdata->appointments[i].time.min + clinicdata->appointments[i + 1].time.min;
                                clinicdata->appointments[i + 1].time.min = clinicdata->appointments[i].time.min - clinicdata->appointments[i + 1].time.min;
                                clinicdata->appointments[i].time.min = clinicdata->appointments[i].time.min - clinicdata->appointments[i + 1].time.min;
                                clinicdata->appointments[i].Patientnumber = clinicdata->appointments[i].Patientnumber + clinicdata->appointments[i + 1].Patientnumber;
                                clinicdata->appointments[i + 1].Patientnumber = clinicdata->appointments[i].Patientnumber - clinicdata->appointments[i + 1].Patientnumber;
                                clinicdata->appointments[i].Patientnumber = clinicdata->appointments[i].Patientnumber - clinicdata->appointments[i + 1].Patientnumber;
                            }
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < clinicdata->maxAppointments; i++)
    {
        if (clinicdata->appointments[i].Patientnumber != 0)
        {
            displayScheduleData(clinicdata->patients + findPatientIndexByPatientNum(clinicdata->appointments[i].Patientnumber, clinicdata->patients, clinicdata->maxAppointments), clinicdata->appointments + i, 1);
        }
    }
    putchar('\n');
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(const struct ClinicData* clinicdata)
{
    int i, year=27, month, day = 27;
    printf("Year        : ");
    scanf("%d", &year);
    printf("Month (1-12): ");
    month = inputIntRange(1, 12);
    if (month == 2)
    {
        if (year % 4 == 0)
        {
            printf("Day (1-29)  : ");
            day = inputIntRange(1, 29);
        }
        else
        {
            printf("Day (1-28)  : ");
            day = inputIntRange(1, 28);
        }
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        printf("Day (1-31)  : ");
        day = inputIntRange(1, 31);
    }
    else
    {
        printf("Day (1-30)  : ");
        day = inputIntRange(1, 30);
    }
    putchar('\n');
    for (i = 0; i < clinicdata->maxAppointments; i++)
    {
        if (clinicdata->appointments[i].date.day == day && clinicdata->appointments[i].date.year == year && clinicdata->appointments[i].date.month == month)
        {
            break;
        }
    }
    displayScheduleTableHeader(&clinicdata->appointments[i].date, 0);
    for (i = 0; i < clinicdata->maxAppointments; i++)
    {
        if (clinicdata->appointments[i].date.year == year && clinicdata->appointments[i].date.month == month && clinicdata->appointments[i].date.day == day)
        {
            displayScheduleData(clinicdata->patients + findPatientIndexByPatientNum(clinicdata->appointments[i].Patientnumber, clinicdata->patients, clinicdata->maxAppointments), clinicdata->appointments + i, 0);
        }
    }
    putchar('\n');
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient)
{
    int patientnumber, exist, j;
    int year, month, day, hour, min;
    
        printf("Patient Number: ");
        scanf("%d", &patientnumber);
        clearInputBuffer();
        exist = findPatientIndexByPatientNum(patientnumber, patients, maxPatient);
        if (exist + 1)
        {
            date:
            printf("Year        : ");
            year = inputIntRange(2000, 3000);
            printf("Month (1-12): ");
            month = inputIntRange(1, 12);
            if (month == 2)
            {
                if (year % 4 == 0)
                {
                    printf("Day (1-29)  : ");
                    day = inputIntRange(1, 29);
                }
                else
                {
                    printf("Day (1-28)  : ");
                    day = inputIntRange(1, 28);
                }
            }
            else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
            {
                printf("Day (1-31)  : ");
                day = inputIntRange(1, 31);
            }
            else
            {
                printf("Day (1-30)  : ");
                day = inputIntRange(1, 30);
            }
            time:
            printf("Hour (0-23)  : ");
            hour = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            min = inputIntRange(0, 59);
            for ( j = 0; j < maxAppointments; j++)
            {
                if (year == appointments[j].date.year && month == appointments[j].date.month && day == appointments[j].date.day && hour == appointments[j].time.hour && min == appointments[j].time.min)
                {
                    printf("\nERROR: Appointment timeslot is not available!\n\n");
                    goto date;
                }
            }
            for (j = 0; j < maxAppointments; j++)
            {
                if (hour >= start && hour <= end)
                {
                    if (hour == end)
                    {
                        if (min == 0)
                        {
                            if (appointments[j].date.year == 0)
                            {
                                appointments[j].date.year = year;
                                appointments[j].date.month = month;
                                appointments[j].date.day = day;
                                appointments[j].time.hour = hour;
                                appointments[j].time.min = min;
                                appointments[j].Patientnumber = patientnumber;
                                printf("\n*** Appointment scheduled! ***\n\n");
                                break;
                            }
                        }
                        else
                        {
                            printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n");
                            goto time;
                        }
                    }
                    else if (min == 0 || min == 30)
                    {
                        if (appointments[j].date.year == 0)
                        {
                            appointments[j].date.year = year;
                            appointments[j].date.month = month;
                            appointments[j].date.day = day;
                            appointments[j].time.hour = hour;
                            appointments[j].time.min = min;
                            appointments[j].Patientnumber = patientnumber;
                            printf("\n*** Appointment scheduled! ***\n\n");
                            break;
                        }
                    }
                    else
                    {
                        printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n");
                        goto time;
                    }
                }
                else
                {
                    printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n");
                    goto time;
                }
            }
        }
        else
            printf("\nERROR: Patient record not found!\n\n");
    
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient)
{
    int patientnumber, exist, i;
    int year, month, day;
    char decision;
    printf("Patient Number: ");
    scanf("%d", &patientnumber);
    clearInputBuffer();
    exist = findPatientIndexByPatientNum(patientnumber, patients, maxPatient);
    if (exist + 1)
    {
        printf("Year        : ");
        year = inputIntRange(2000, 3000);
        printf("Month (1-12): ");
        month = inputIntRange(1, 12);
        if (month == 2)
        {
            if (year % 4 == 0)
            {
                printf("Day (1-29)  : ");
                day = inputIntRange(1, 29);
            }
            else
            {
                printf("Day (1-28)  : ");
                day = inputIntRange(1, 28);
            }
        }
        else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        {
            printf("Day (1-31)  : ");
            day = inputIntRange(1, 31);
        }
        else
        {
            printf("Day (1-30)  : ");
            day = inputIntRange(1, 30);
        }       
        putchar('\n');
        displayPatientData(patients + exist, FMT_FORM);
        printf("Are you sure you want to remove this appointment (y,n): ");
        decision = inputCharOption("yn");
        if (decision == 'y')
        {
            for ( i = 0; i < maxAppointments; i++)
            {
                if (appointments[i].Patientnumber == patientnumber && appointments[i].date.year == year && appointments[i].date.month == month && appointments[i].date.day == day)
                {
                    break;
                }
            }
            appointments[i].Patientnumber = 0;
            appointments[i].date.year = 0;
            appointments[i].date.month = 0;
            appointments[i].date.day = 0;
            printf("\nAppointment record has been removed!\n\n");
        }
        else
            printf("Operation aborted.\n\n");
    }
    else
        printf("ERROR: Patient record not found!\n\n");
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientnumber, patientindex;
    printf("Search by patient number: ");
    scanf("%d", &patientnumber);
    clearInputBuffer();
    patientindex = findPatientIndexByPatientNum(patientnumber, patient, max);
    putchar('\n');
    if (patientindex != -1)
    {
        displayPatientData(patient + patientindex, FMT_FORM);
    }
    else
        printf("*** No records found ***\n");
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i, check = 0;
    char phonenumber[11];
    printf("Search by phone number: ");
    scanf("%s", phonenumber);
    clearInputBuffer();
    putchar('\n');
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (phonenumber[0] == patient[i].phone.number[0] && phonenumber[1] == patient[i].phone.number[1] && phonenumber[2] == patient[i].phone.number[2] && phonenumber[3] == patient[i].phone.number[3] && phonenumber[4] == patient[i].phone.number[4] && phonenumber[5] == patient[i].phone.number[5] && phonenumber[6] == patient[i].phone.number[6] && phonenumber[7] == patient[i].phone.number[7] && phonenumber[8] == patient[i].phone.number[8])
        {
            displayPatientData(patient + i, FMT_TABLE);
            check++;
        }
        else if (i == max - 1 && check == 0)
        {
            printf("\n*** No records found ***\n");
        }
    }
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i, patientNumber = patient[0].patientNumber;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > patientNumber)
        {
            patientNumber = patient[i].patientNumber;
        }
    }
    patientNumber++;
    return patientNumber;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i;
    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            return i;
        }
    }
    return -1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: ");
    printf("0%d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, 15);
    putchar('\n');
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int phoneselection, i = 0;
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n2. Home\n3. Work\n4. TBD\nSelection: ");
    phoneselection = inputIntRange(1, 4);
    putchar('\n');
    switch (phoneselection)
    {
    case 1:
        i = 0;
        printf("Contact: ");
        phone->description[0] = 'C';
        phone->description[1] = 'E';
        phone->description[2] = 'L';
        phone->description[3] = 'L';
        phone->description[4] = '\0';
        printf("%c%c%c%c\n", phone[0].description[0], phone[0].description[1], phone[0].description[2], phone[0].description[3]);
    scan:
        if (i)
        {
            i = 0;
            printf("Number: ");
        }
        else
            printf("Number : ");
        scanf("%s", phone->number);
        if (strlen(phone->number) != 10)
        {
            printf("Invalid 10-digit number! ");
            clearInputBuffer();
            i++;
            goto scan;
        }
        clearInputBuffer();
        break;
    case 2:
        i = 0;
        printf("Contact: ");
        phone->description[0] = 'H';
        phone->description[1] = 'O';
        phone->description[2] = 'M';
        phone->description[3] = 'E';
        printf("%c%c%c%c\n", phone[0].description[0], phone[0].description[1], phone[0].description[2], phone[0].description[3]);
    scan2:
        if (i != 0)
        {
            i = 0;
            printf("Number: ");
        }
        else
            printf("Number : ");
        scanf("%s", phone->number);
        if (strlen(phone->number) != 10)
        {
            printf("Invalid 10-digit number! ");
            clearInputBuffer();
            i++;
            goto scan2;
        }
        clearInputBuffer();
        break;
    case 3:
        i = 0;
        printf("Contact: ");
        phone->description[0] = 'W';
        phone->description[1] = 'O';
        phone->description[2] = 'R';
        phone->description[3] = 'K';
        printf("%c%c%c%c\n", phone[0].description[0], phone[0].description[1], phone[0].description[2], phone[0].description[3]);
    scan3:
        if (i != 0)
        {
            i = 0;
            printf("Number: ");
        }
        else
            printf("Number : ");
        scanf("%s", phone->number);
        if (strlen(phone->number) != 10)
        {
            printf("Invalid 10-digit number! ");
            clearInputBuffer();
            i++;
            goto scan3;
        }
        clearInputBuffer();
        break;
    case 4:
        phone->description[0] = 'T';
        phone->description[1] = 'B';
        phone->description[2] = 'D';
        break;
    }
    if (phoneselection != 4)
    {
        putchar('\n');
    }
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0;
    FILE* file = fopen(datafile, "r");
    for (i = 0; i < max; i++)
    {
        fscanf(file, "%d|%[^|]|%[^|]|%[^\n]",
                &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number);
        patients[i].phone.number[10] = '\0';
    }
    fclose(file);
    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;
    FILE* file = fopen(datafile, "r");
    for (i = 0; i < max; i++)
    {        
        fscanf(file, "%d,%d,%d,%d,%d,%d", &appoints[i].Patientnumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min);
        if (appoints[i].Patientnumber == 0)
        {
            break;
        }
    }
    fclose(file);
    return i;
}