#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
    char name[32],equippedBy[32];
    float code;
    int level;
} rune;

typedef struct{
    char name[32],damageType[32],equippedBy[32];
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

int findCharacter(character *vetCharacters[],int lenCharacters,char charName[],int print){
    for(int i=0;i<lenCharacters;i++){
        if(strcmp(vetCharacters[i]->name,charName)==0){
            return i;
        }
    }
    if(print==1){
        printf("\nThere is no character with this name!\n\n");
    }
    return -1;
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

int findCharacterInParty(character *vetParty[], int lenParty, char charName[], int print){
    for(int i=0;i<lenParty;i++){
        if(strcmp(vetParty[i]->name,charName)==0){
            return i;
        }
    }
    if(print==1){
        printf("\nThis character is not in the party\n\n");
    }
    return -1;
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
    strcpy(newWeapon->equippedBy,"-");

    vetWeapons[*lenWeapons] = newWeapon;
    (*lenWeapons)++;

    printf("\n%s was successfully created!\n\n",newWeapon->name);
    return 1;
}

int findWeaponInCharacter(character *vetCharacters[], int indexCharacter, char weaponName[], int print){
    for(int i=0;i<vetCharacters[indexCharacter]->lenCharWeapons;i++){
        if(strcmp(vetCharacters[indexCharacter]->charWeapons[i]->name,weaponName)==0){
            return i;
        }
    }
    if(print==1){
        printf("\n%s is not equipped by %s\n\n",weaponName,vetCharacters[indexCharacter]->name);
    }
    return -1;
}

int addWeaponToCharacter(weapon *vetWeapons[], character *vetCharacters[], int indexWeapon, int indexCharacter){
    if(strcmp(vetWeapons[indexWeapon]->equippedBy,"-")!=0){
        printf("\n%s is already equipped by a character\n\n",vetWeapons[indexWeapon]->name);
        return -1;
    }
    if(vetCharacters[indexCharacter]->lenCharWeapons>=2){
        printf("\nCharacter inventory is full!\n\n");
        return -1;
    }
    vetCharacters[indexCharacter]->charWeapons[vetCharacters[indexCharacter]->lenCharWeapons]=vetWeapons[indexWeapon];
    strcpy(vetWeapons[indexWeapon]->equippedBy,vetCharacters[indexCharacter]->name);
    (vetCharacters[indexCharacter]->lenCharWeapons)++;
    printf("\n%s was successfully added to %s's inventory!\n\n",vetWeapons[indexWeapon]->name,vetCharacters[indexCharacter]->name);
    return 1;
}

int removeWeaponFromCharacter(weapon *vetWeapons[], character *vetCharacters[], int indexWeapon, int indexCharacter){
    int indexToRemove = findWeaponInCharacter(vetCharacters,indexCharacter,vetWeapons[indexWeapon]->name,1);
    char *weaponName = vetWeapons[indexWeapon]->name;

    if(indexToRemove!=-1){
        for(int i=indexToRemove;i<vetCharacters[indexCharacter]->lenCharWeapons-1;i++){
        vetCharacters[indexCharacter]->charWeapons[i]=vetCharacters[indexCharacter]->charWeapons[i+1];
        }
    strcpy(vetWeapons[indexWeapon]->equippedBy,"-");
    printf("\n%s was removed from %s inventory.\n\n",weaponName,vetCharacters[indexCharacter]->name);
    (vetCharacters[indexCharacter]->lenCharWeapons)--;
    return 1;
    }
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

int findRuneInWeapon(rune *vetRunes[], weapon *vetWeapons[], int indexWeapon, char runeName[], int print){
    for(int i=0;i<vetWeapons[indexWeapon]->lenWeaponRunes;i++){
        if(strcmp(vetWeapons[indexWeapon]->runes[0]->name,runeName)==0){
            return i;
        }
    }
    if(print==1){
        printf("\n%s is not equipped by %s\n\n",runeName,vetWeapons[indexWeapon]->name);
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
    strcpy(newRune->equippedBy,"-");

    vetRunes[*lenRunes] = newRune;
    (*lenRunes)++;

    printf("\nRune was successfully created!\n\n");
    return 1;
}

int addRuneToWeapon(rune *vetRunes[], weapon *vetWeapons[], int indexRune, int indexWeapon){
    if(strcmp(vetRunes[indexRune]->equippedBy,"-")!=0){
        printf("\n%s is already equipped by a weapon\n\n",vetRunes[indexRune]->name);
        return -1;
    }
    if(vetWeapons[indexWeapon]->lenWeaponRunes>=4){
        printf("\n%s is already full of runes!\n\n",vetWeapons[indexWeapon]->name);
        return -1;
    }

    vetWeapons[indexWeapon]->runes[vetWeapons[indexWeapon]->lenWeaponRunes]=vetRunes[indexRune];
    strcpy(vetRunes[indexRune]->equippedBy,vetWeapons[indexWeapon]->name);
    (vetWeapons[indexWeapon]->lenWeaponRunes)++;
    printf("\n%s was successfully added to %s\n\n",vetRunes[indexRune]->name,vetWeapons[indexWeapon]->name);
    return 1;
}

int removeRuneFromWeapon(rune *vetRunes[], weapon *vetWeapons[], int indexRune, int indexWeapon){
    int indexToRemove = findRuneInWeapon(vetRunes,vetWeapons,indexWeapon,vetRunes[indexRune]->name,1);
    char *runeName = vetRunes[indexRune]->name;

    if(indexToRemove!=-1){
        for(int i=indexToRemove;i<vetWeapons[indexWeapon]->lenWeaponRunes-1;i++){
        vetWeapons[indexWeapon]->runes[i]=vetWeapons[indexWeapon]->runes[i+1];
        }
    strcpy(vetRunes[indexRune]->equippedBy,"-");
    (vetWeapons[indexWeapon]->lenWeaponRunes)--;
    printf("\n%s was successfully removed from %s\n\n",runeName,vetWeapons[indexWeapon]->name);
    return 1;
    }
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

int removeFromParty(character *vetParty[], int *lenParty, int indexCharacterInParty){
    char *name = vetParty[indexCharacterInParty]->name;
    for(int i=indexCharacterInParty;i<*lenParty-1;i++){
        vetParty[i]=vetParty[i+1];
    }
    (*lenParty)--;
    printf("\n%s was removed from the party.\n\n",name);
    return 1;
}

void showRunes(rune *vetRunes[], int lenRunes){
    printf("\n\n----------All Runes----------\n\n");
    for(int i=0;i<lenRunes;i++){
        printf("##### Rune %d #####\n\n",i+1);
        printf("Name: %s\n",vetRunes[i]->name);
        printf("Code: %.1f\n",vetRunes[i]->code);
        printf("Level: %d\n",vetRunes[i]->level);
        printf("Equipped by: %s\n\n",vetRunes[i]->equippedBy);
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
        printf("\n");
        printf("Equipped by: %s\n\n",vetWeapons[i]->equippedBy);
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
        if(vetParty[i]->lenCharWeapons!=0){
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

int deleteCharacter(character *vetCharacters[], int *lenCharacters, int indexCharacter){
    char *charName = vetCharacters[indexCharacter]->name;
    for(int i=indexCharacter;i<*lenCharacters-1;i++){
        vetCharacters[i]=vetCharacters[i+1];
    }
    printf("\n%s was deleted.\n\n",charName);
    (*lenCharacters)--;
    return 1;
}

int deleteWeapon(weapon *vetWeapons[], int *lenWeapons, int indexWeapon){
    char *weaponName = vetWeapons[indexWeapon]->name;
    for(int i=indexWeapon;i<*lenWeapons-1;i++){
        vetWeapons[i]=vetWeapons[i+1];
    }
    (*lenWeapons)--;
    printf("\n%s was deleted.\n\n",weaponName);
    return 1;
}

int deleteRune(rune *vetRunes[], int *lenRunes, int indexRune){
    char *runeName = vetRunes[indexRune]->name;
    for(int i=indexRune;i<*lenRunes-1;i++){
        vetRunes[i]=vetRunes[i+1];
    }
    (*lenRunes)--;
    printf("\n%s was deleted.\n\n",runeName);
    return 1;
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
        printf("10- Delete character\n");
        printf("11- Delete weapon\n");
        printf("12- Delete rune\n");
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
            int indexCharacterInParty = findCharacterInParty(party,lenParty,name,1);
            if(indexCharacterInParty!=-1){
                removeFromParty(party,&lenParty,indexCharacterInParty);
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
            char charName[32];
            getName(charName,"Character");
            int indexCharacter = findCharacter(characters,lenCharacters,charName,1);
            if(indexCharacter!=-1){
                int indexCharacterInParty = findCharacterInParty(party,lenParty,charName,0);
                if(indexCharacterInParty!=-1){
                    removeFromParty(party,&lenParty,indexCharacterInParty);
                }
                for(int i=characters[indexCharacter]->lenCharWeapons-1;i>=0;i--){
                    int indexWeapon = findWeapon(weapons,lenWeapons,characters[indexCharacter]->charWeapons[i]->name,0);
                    removeWeaponFromCharacter(weapons,characters,indexWeapon,indexCharacter);
                }
                deleteCharacter(characters,&lenCharacters,indexCharacter);
            }
        }else if(option==11){
            char weaponName[32];
            getName(weaponName,"Weapon");
            int indexWeapon = findWeapon(weapons,lenWeapons,weaponName,1);
            if(indexWeapon!=-1){
                if(strcmp(weapons[indexWeapon]->equippedBy,"-")!=0){
                    int indexCharacter = findCharacter(characters,lenCharacters,weapons[indexWeapon]->equippedBy,0);
                    removeWeaponFromCharacter(weapons,characters,indexWeapon,indexCharacter);
                    for(int i=weapons[indexWeapon]->lenWeaponRunes-1;i>=0;i--){
                        int indexRune = findRune(runes,lenRunes,weapons[indexWeapon]->runes[i]->name,0);
                        removeRuneFromWeapon(runes,weapons,indexRune,indexWeapon);
                    }
                }
                deleteWeapon(weapons,&lenWeapons,indexWeapon);
            }
        }else if(option==12){
            char runeName[32];
            getName(runeName,"Rune");
            int indexRune = findRune(runes,lenRunes,runeName,1);
            if(indexRune!=-1){
                if(strcmp(runes[indexRune]->equippedBy,"-")!=0){
                    int indexWeapon = findWeapon(weapons,lenWeapons,runes[indexRune]->equippedBy,0);
                    removeRuneFromWeapon(runes,weapons,indexRune,indexWeapon);
                }
                deleteRune(runes,&lenRunes,indexRune);
            }
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

    freeRunes(runes,lenRunes);
    freeWeapons(weapons,lenWeapons);
    freeCharacters(characters,lenCharacters);
    free(characters);
    free(weapons);
    free(runes);
    free(party);

    return 0;
}