#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ui.h"
#include "client.h"
#include <time.h>


void print_menu() {
    printf("\n======== Chat Menu ========\n");
    printf("1. Send Broadcast Message\n");
    printf("2. Private Chat Session (Continuous)\n");
    printf("3. Retrieve Chat History\n");
    printf("4. List Online Users\n");
    printf("5. List All Registered Users\n");
    printf("6. Send File\n");
    printf("7. Logout\n");
    printf("===========================\n");
    printf("Enter your choice: ");
}

void authenticate(int sockfd, char *username, size_t username_size) {
    char option[10];
    char password[32];
    char user_id[32];
    char buffer[512];
    int choice;
    
    while (1) {
        printf("\n====== Welcome to Chat Client ======\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("Enter choice: ");
        if (!fgets(option, sizeof(option), stdin))
            continue;
        choice = atoi(option);
        if (choice == 1) {
            printf("Enter desired username: ");
            if (!fgets(username, username_size, stdin))
                continue;
            username[strcspn(username, "\n")] = '\0';
            printf("Enter desired password: ");
            if (!fgets(password, sizeof(password), stdin))
                continue;
            password[strcspn(password, "\n")] = '\0';
            snprintf(buffer, sizeof(buffer), "REGISTER %s %s\n", username, password);
            write(sockfd, buffer, strlen(buffer));
            sleep(2);
            break;  // Assume auto‑login after registration.
        } else if (choice == 2) {
            printf("Enter user_id: ");
            if (!fgets(user_id, username_size, stdin))
                continue;
            user_id[strcspn(user_id, "\n")] = '\0';
            printf("Enter password: ");
            if (!fgets(password, sizeof(password), stdin))
                continue;
            password[strcspn(password, "\n")] = '\0';
            snprintf(buffer, sizeof(buffer), "LOGIN %s %s\n", user_id, password);
            write(sockfd, buffer, strlen(buffer));
            // username=user_id;
            strncpy(username,user_id,username_size-1);
            username[username_size-1]='\0';
              sleep(3);
            break;
        } else {
            printf("Invalid choice, try again.\n");
        }
    }
}
