#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
    char name[32];
    float code;
    int level;
} rune;

typedef struct{
    char name[32],damageType[32];
    int damageValue, lenWeaponRunes, level;
    float range, weigth;
    rune *runes[4];
} weapon;

typedef struct{
    char name[32];
    int hp, strength, speed, level, lenCharWeapons;
    weapon *charWeapons[2];
} character;

void bufferCleaner(){
    char c;
    while((c=getchar())!='\n'){
    }
}

void removeEnter(char string[]){
    size_t len = strlen(string);
    if(string[len-1]=='\n'){
        string[len-1]='\0';
    }
}

void getName(char name[],char type[]){
    printf("%s name:",type);
    fgets(name,32,stdin);
    removeEnter(name);
}

int createCharacter(character *vetCharacters[], int *lenCharacters){
    character *newCharacter = malloc(sizeof(character));

    char testName[32];
    getName(testName,"Character");
    if(findCharacter(vetCharacters,*lenCharacters,testName,0)!=-1){
        printf("A character with this name already existis!\n\n");
        return -1;
    }
    strcpy(newCharacter->name,testName);

    printf("Character HP:");
    scanf("%d",&newCharacter->hp);

    printf("Character strength:");
    scanf("%d",&newCharacter->strength);

    printf("Character speed:");
    scanf("%d",&newCharacter->speed);

    newCharacter->level = 1;
    newCharacter->lenCharWeapons = 0;

    vetCharacters[*lenCharacters] = newCharacter;
    (*lenCharacters)++;

    printf("\n%s was successfully created!\n\n",newCharacter->name);
    return 1;
}

int findCharacter(character *vetCharacters[],int lenCharacters,char charName[],int print){
    int index;

    for(int i=0;i<lenCharacters;i++){
        if(strcmp(vetCharacters[i]->name,charName)==0){
            return i;
        }
    }
    if(print==1){
        printf("There is no character with this name!\n\n");
    }
    return -1;
}

int createWeapon(weapon *vetWeapons[], int *lenWeapons){
    weapon *newWeapon =  malloc(sizeof(weapon)); 
    
    char testName[32];
    getName(testName,"Weapon");

    if(findWeapon(vetWeapons,*lenWeapons,testName,0)!=-1){
        printf("A weapon with this name already exists!\n\n");
        return -1;
    }
    strcpy(newWeapon->name,testName);

    printf("Damage type:");
    fgets(newWeapon->damageType,32,stdin);
    removeEnter(newWeapon->damageType);

    printf("Damage value:");
    scanf("%d",&newWeapon->damageValue);

    printf("Range:");
    scanf("%f",&newWeapon->range);

    printf("Weigth:");
    scanf("%f",&newWeapon->weigth);

    newWeapon->level=1;
    newWeapon->lenWeaponRunes=0;

    vetWeapons[*lenWeapons] = newWeapon;
    (*lenWeapons)++;

    printf("\n%s was successfully created!\n\n",newWeapon->name);
    return 1;
}

int findWeapon(weapon *vetWeapons[], int lenWeapons, char weaponName[],int print){
    for(int i=0;i<lenWeapons;i++){
        if(strcmp(vetWeapons[i]->name,weaponName)==0){
            return i;
        }
    }
    if(print==1){
        printf("\nThere is no weapon with this name!\n\n");
    }
    return -1;
}

int addWeaponToCharacter(weapon *vetWeapons[], character *vetCharacters[], int indexWeapon, int indexCharacter){
    if(vetCharacters[indexCharacter]->lenCharWeapons<2){
        for(int i=0;i<vetCharacters[indexCharacter]->lenCharWeapons;i++){
            if(strcmp(vetCharacters[indexCharacter]->charWeapons[i]->name,vetWeapons[indexWeapon]->name)==0){
            printf("\n%s has already equipped %s\n\n",vetCharacters[indexCharacter]->name,vetWeapons[indexWeapon]->name);
            return -1;
            }
        }
        vetCharacters[indexCharacter]->charWeapons[vetCharacters[indexCharacter]->lenCharWeapons]=vetWeapons[indexWeapon];
        (vetCharacters[indexCharacter]->lenCharWeapons)++;
        printf("\n%s was successfully added to %s's inventory!\n\n",vetWeapons[indexWeapon]->name,vetCharacters[indexCharacter]->name);
        return 1;
    }
    printf("\nCharacter inventory is full!\n\n");
    return -1;
}

int removeWeaponFromCharacter(weapon *vetWeapons[], character *vetCharacters[], int indexWeapon, int indexCharacter){
    for(int i=0;i<vetCharacters[indexCharacter]->lenCharWeapons;i++){
        if(strcmp(vetWeapons[indexWeapon]->name,vetCharacters[indexCharacter]->charWeapons[i]->name)==0){
            for(int j=i;j<(vetCharacters[indexCharacter]->lenCharWeapons)-1;j++){
                vetCharacters[indexCharacter]->charWeapons[j]=vetCharacters[indexCharacter]->charWeapons[j+1];
            }
            printf("\n%s was removed from %s inventory.\n\n",vetWeapons[indexWeapon]->name,vetCharacters[indexCharacter]->name);
            (vetCharacters[indexCharacter]->lenCharWeapons)--;
            return 1;
        }
    }
    printf("\n%s was already not in %s inventory.\n\n",vetCharacters[indexCharacter]->name,vetWeapons[indexWeapon]->name);
    return -1;
}

float validateRuneCode(float code){
    if(code>=1 && code<4.95){
        float codeF = roundf(code*10)/10;
        return codeF;
    }
    printf("\nThe rune code must be a number between 1 and 4.9\n\n");
    return -1;
}

int findRune(rune *vetRunes[], int lenRunes, char runeName[], int print){
    for(int i=0;i<lenRunes;i++){
        if(strcmp(vetRunes[i]->name,runeName)==0){
            return i;
        }
    }
    if(print==1){
        printf("\nThere is no rune with this name!\n\n");
    }
    return -1; 
}

int createRune(rune *vetRunes[],int *lenRunes){
    rune *newRune = malloc(sizeof(rune));

    printf("Rune code:");
    float runeCode;
    scanf("%f",&runeCode);
    runeCode = validateRuneCode(runeCode);
    if(runeCode==-1){
        return -1;
    }
    newRune->code = runeCode;

    bufferCleaner();
    char testName[32];
    getName(testName,"Rune");
    if(findRune(vetRunes,*lenRunes,testName,0)!=-1){
        printf("\nA rune with this name already exists!\n\n");
        return -1;
    }
    strcpy(newRune->name,testName);

    newRune->level = 1;

    vetRunes[*lenRunes] = newRune;
    (*lenRunes)++;

    printf("\nRune was successfully created!\n\n");
    return 1;
}

int addRuneToWeapon(rune *vetRunes[], weapon *vetWeapons[], int indexRune, int indexWeapon){
    if(vetWeapons[indexWeapon]->lenWeaponRunes<4){
        for(int i=0;i<vetWeapons[indexWeapon]->lenWeaponRunes;i++){
            if(strcmp(vetWeapons[indexWeapon]->runes[i]->name,vetRunes[indexRune]->name)==0){
                printf("\n%s has already equipped %s\n\n",vetWeapons[indexWeapon]->name,vetRunes[indexRune]->name);
                return -1;
            }
        }
        vetWeapons[indexWeapon]->runes[vetWeapons[indexWeapon]->lenWeaponRunes]=vetRunes[indexRune];
        (vetWeapons[indexWeapon]->lenWeaponRunes)++;
        printf("\n%s was successfully added to %s\n\n",vetRunes[indexRune]->name,vetWeapons[indexWeapon]->name);
        return 1;
    }
    printf("\n%s runes space is full!\n\n",vetWeapons[indexWeapon]->name);
    return -1;
}

int removeRuneFromWeapon(rune *vetRunes[], weapon *vetWeapons[], int indexRune, int indexWeapon){
    for(int i=0;i<vetWeapons[indexWeapon]->lenWeaponRunes;i++){
        if(strcmp(vetWeapons[indexWeapon]->runes[i]->name,vetRunes[indexRune]->name)==0){
            for(int j=i;j<vetWeapons[indexWeapon]->lenWeaponRunes-1;j++){
                vetWeapons[indexWeapon]->runes[j]=vetWeapons[indexWeapon]->runes[j+1];
            }
            (vetWeapons[indexWeapon]->lenWeaponRunes)--; 
            printf("\n%s was successfully removed from %s\n\n",vetRunes[indexRune]->name,vetWeapons[indexWeapon]->name);
            return 1;
        }
    }
    printf("\n%s was already not equipped\n\n",vetRunes[indexRune]->name);
    return -1;
}

void showCharacters(character *vetCharacters[],int len){
    printf("\n\n----------All Characters----------\n\n");
    for(int i=0;i<len;i++){
            printf("##### Character %d #####\n\n",i+1);
        printf("Name: %s\n",vetCharacters[i]->name);
        printf("HP: %d\n",vetCharacters[i]->hp);
        printf("Stength: %d\n",vetCharacters[i]->strength);
        printf("Speed: %d\n",vetCharacters[i]->speed);
        printf("Level: %d\n",vetCharacters[i]->level);
        printf("Weapons: ||");
        if(vetCharacters[i]->lenCharWeapons!=0){
            for(int j=0;j<vetCharacters[i]->lenCharWeapons;j++){
                printf("  %s (",vetCharacters[i]->charWeapons[j]->name);
                for(int l=0;l<vetCharacters[i]->charWeapons[j]->lenWeaponRunes;l++){
                    printf(" %.1f",vetCharacters[i]->charWeapons[j]->runes[l]->code);
                }
                printf(" )  ||");
            }
        }
        printf("\n\n");
    }
}

int addToParty(character *vetParty[], character *vetCharacters[], int *lenParty, int indexCharacter){
    if(*lenParty<4){
        for(int i=0;i<*lenParty;i++){
            if(strcmp(vetParty[i]->name,vetCharacters[indexCharacter]->name)==0){
                printf("The character is already in the party!\n\n");
                return -1;
            }
        }
        vetParty[*lenParty]=vetCharacters[indexCharacter];
        (*lenParty)++;
        printf("\n%s has joined the party!\n\n",vetCharacters[indexCharacter]->name);
        return 1;
    }
    printf("\nParty is full!\n\n");
    return -1;
}

int removeFromParty(character *vetParty[], character *vetCharacters[], int *lenParty, int indexCharacter){
    if(*lenParty>0){
        for(int i=0;i<*lenParty-1;i++){
            vetParty[i]=vetParty[i+1];
        }
        (*lenParty)--;
        printf("\n%s was removed from the party.\n\n",vetCharacters[indexCharacter]->name);
        return 1;
    }
    printf("\n%s was already not in the party.\n\n",vetCharacters[indexCharacter]->name);
    return -1;
}

void showRunes(rune *vetRunes[], int lenRunes){
    printf("\n\n----------All Runes----------\n\n");
    for(int i=0;i<lenRunes;i++){
        printf("##### Rune %d #####\n\n",i+1);
        printf("Name: %s\n",vetRunes[i]->name);
        printf("Code: %.1f\n",vetRunes[i]->code);
        printf("Level: %d\n\n",vetRunes[i]->level);
    }
}

void showWeapons(weapon *vetWeapons[], int lenWeapons){
    printf("\n\n----------All Weapons----------\n\n");
    for(int i=0;i<lenWeapons;i++){
        printf("##### Weapon %d#####\n\n",i+1);
        printf("Name: %s\n",vetWeapons[i]->name);
        printf("Damage type: %s\n",vetWeapons[i]->damageType);
        printf("Damage value: %d\n",vetWeapons[i]->damageValue);
        printf("Range: %.1f\n",vetWeapons[i]->range);
        printf("Weigth: %.1f\n",vetWeapons[i]->weigth);
        printf("Level: %d\n",vetWeapons[i]->level);
        printf("Runes:");
        for(int j=0;j<vetWeapons[i]->lenWeaponRunes;j++){
            printf(" %.1f",vetWeapons[i]->runes[j]->code);
        }
        printf("\n\n");
    }
}

void showParty(character *vetParty[], int lenParty){
    printf("\n\n----------Party----------\n\n");
    for(int i=0;i<lenParty;i++){
        printf("##### Character %d #####\n\n",i+1);
        printf("Name: %s\n",vetParty[i]->name);
        printf("HP: %d\n",vetParty[i]->hp);
        printf("Strength: %d\n",vetParty[i]->strength);
        printf("Speed: %d\n",vetParty[i]->speed);
        printf("Level: %d\n",vetParty[i]->level);
        printf("Weapons: ||");
        if(vetParty[i]->charWeapons!=0){
            for(int j=0;j<vetParty[i]->lenCharWeapons;j++){
                printf("  %s (",vetParty[i]->charWeapons[j]->name);
                for(int l=0;l<vetParty[i]->charWeapons[j]->lenWeaponRunes;l++){
                    printf(" %.1f",vetParty[i]->charWeapons[j]->runes[l]->code);
                }
                printf(" ) ||");
            }
        }
        printf("\n\n");
    }
}

void freeCharacters(character *vetCharacters[], int lenCharacters){
    for(int i=0;i<lenCharacters;i++){
        free(vetCharacters[i]);
    }
}

void freeWeapons(weapon *vetWeapons[], int lenWeapons){
    for(int i=0;i<lenWeapons;i++){
        free(vetWeapons[i]);
    }
}

void freeRunes(rune *vetRunes[], int lenRunes){
    for(int i=0;i<lenRunes;i++){
        free(vetRunes[i]);
    }
}

int main(){
    weapon **weapons = malloc(sizeof(weapon*)*20);
    rune **runes = malloc(sizeof(rune*)*80);
    character **characters = malloc(sizeof(character*)*10);
    character **party = malloc(sizeof(character*)*4);
    int option=0,lenWeapons=0,lenRunes=0,lenCharacters=0,lenParty=0;

    while(option!=-1){
        printf("1- Create character\n");
        printf("2- Add to party\n");
        printf("3- Remove from party\n");
        printf("4- Create weapon\n");
        printf("5- Add weapon to character\n");
        printf("6- Remove weapon from character\n");
        printf("7- Create rune\n");
        printf("8- Add rune to weapon\n");
        printf("9- Remove rune from weapon\n");
        printf("10- Delete character (UNAVAILABLE)\n");
        printf("11- Delete weapon (UNAVAILABLE)\n");
        printf("12- Delete rune (UNAVAILABLE)\n");
        printf("13- Show party\n");
        printf("14- Show characters\n");
        printf("15- Show weapons\n");
        printf("16- Show runes\n");
        printf("\nChoose an option:");
        scanf("%d",&option);
        bufferCleaner();

        if(option==1){
            createCharacter(characters,&lenCharacters);
        }else if(option==2){
            char name[32];
            getName(name,"Character");
            int indexCharacter = findCharacter(characters,lenCharacters,name,1);
            if(indexCharacter!=-1){
                addToParty(party,characters,&lenParty,indexCharacter);
            }
        }else if(option==3){
            char name[32];
            getName(name,"Character");
            int indexCharacter = findCharacter(characters,lenCharacters,name,1);
            if(indexCharacter=-1){
                removeFromParty(party,characters,&lenParty,indexCharacter);
            }
        }else if(option==4){
            createWeapon(weapons,&lenWeapons);
        }else if(option==5){
            char weaponName[32];
            getName(weaponName,"Weapon");
            int indexWeapon = findWeapon(weapons,lenWeapons,weaponName,1);
            if(indexWeapon!=-1){
                char charName[32];
                getName(charName,"Character");
                int indexCharacter = findCharacter(characters,lenCharacters,charName,1);
                if(indexCharacter!=-1){
                    addWeaponToCharacter(weapons,characters,indexWeapon,indexCharacter);
                }
            }
        }else if(option==6){
            char weaponName[32];
            getName(weaponName,"Weapon");
            int indexWeapon = findWeapon(weapons,lenWeapons,weaponName,1);
            if(indexWeapon!=-1){
                char charName[32];
                getName(charName,"Character");
                int indexCharacter = findCharacter(characters,lenCharacters,charName,1);
                if(indexCharacter!=-1){
                    removeWeaponFromCharacter(weapons,characters,indexWeapon,indexCharacter);
                }
            }
        }else if(option==7){
            createRune(runes,&lenRunes);
        }else if(option==8){
            char runeName[32];
            getName(runeName,"Rune");
            int indexRune = findRune(runes,lenRunes,runeName,1);
            if(indexRune!=-1){
                char weaponName[32];
                getName(weaponName,"Weapon");
                int indexWeapon = findWeapon(weapons,lenWeapons,weaponName,1);
                if(indexWeapon!=-1){
                    addRuneToWeapon(runes,weapons,indexRune,indexWeapon);
                }
            }
        }else if(option==9){
            char runeName[32];
            getName(runeName,"Rune");
            int indexRune = findRune(runes,lenRunes,runeName,1);
            if(indexRune!=-1){
                char weaponName[32];
                getName(weaponName,"Weapon");
                int indexWeapon = findWeapon(weapons,lenWeapons,weaponName,1);
                if(indexWeapon!=-1){
                    removeRuneFromWeapon(runes,weapons,indexRune,indexWeapon);
                }
            }
        }else if(option==10){
        
        }else if(option==11){

        }else if(option==12){

        }else if(option==13){
            showParty(party,lenParty);
        }else if(option==14){
            showCharacters(characters,lenCharacters);
        }else if(option==15){
            showWeapons(weapons,lenWeapons);
        }else if(option==16){
            showRunes(runes,lenRunes);
        }
    }

    freeCharacters(characters,lenCharacters);
    freeWeapons(weapons,lenWeapons);
    freeRunes(runes,lenRunes);
    free(characters);
    free(weapons);
    free(runes);
    free(party);

    return 0;
}