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
    int damageValue, lenRunes, level;
    float range, weigth;
    rune runes[4];
} weapon;

typedef struct{
    char name[32];
    int hp, strength, speed, level, lenCharWeapons;
    weapon charWeapons[2];
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

int createCharacter(character vet[], int *len){
    char testName[32];
    getName(testName,"Character");
    if(findCharacter(vet,*len,testName,0)!=-1){
        printf("A character with this name already existis!\n\n");
        return -1;
    }
    strcpy(vet[*len].name,testName);

    printf("Character HP:");
    scanf("%d",&vet[*len].hp);

    printf("Character strength:");
    scanf("%d",&vet[*len].strength);

    printf("Character speed:");
    scanf("%d",&vet[*len].speed);

    vet[*len].level = 1;
    vet[*len].lenCharWeapons = 0;

    printf("\n%s was successfully created!\n\n",vet[*len].name);
    (*len)++;
    return 1;
}

int findCharacter(character vet[],int len,char charName[],int print){
    int index;

    for(int i=0;i<len;i++){
        if(strcmp(vet[i].name,charName)==0){
            return i;
        }
    }
    if(print==1){
        printf("There is no character with this name!\n\n");
    }
    return -1;
}

int addToParty(character vetParty[],character vetCharacters[],int *len, int index){
    if(*len<4){
        if(findCharacter(vetParty,*len,vetCharacters[index].name,0)!=-1){
            printf("The character is already in the party!\n\n");
            return -1;
        }
        vetParty[*len]=vetCharacters[index];
        (*len)++;
        printf("\n%s has joined the party!\n\n",vetCharacters[index].name);
        return 1;
    }
    printf("\nParty is full!\n\n");
    return -1;
}

int removeFromParty(character vetParty[], character vetCharacters[], int *len, int indexCharacter){

    int index = findCharacter(vetParty,*len,vetCharacters[indexCharacter].name,0);

    if(index!=-1){
        for(int i=0;i<*len;i++){
            vetParty[i]=vetParty[i+1];
        }
        (*len)--;
        printf("\n%s was removed from the party.\n\n",vetCharacters[indexCharacter].name);
        return 1;
    }
    printf("\n%s was already not in the party.\n\n",vetCharacters[indexCharacter].name);
    return -1;

}

int createWeapon(weapon vetWeapons[], int *len){
    char testName[32];
    getName(testName,"Weapon");

    if(findWeapon(vetWeapons,*len,testName,0)!=-1){
        printf("A weapon with this name already exists!\n\n");
        return -1;
    }
    strcpy(vetWeapons[*len].name,testName);

    printf("Damage type:");
    fgets(vetWeapons[*len].damageType,32,stdin);
    removeEnter(vetWeapons[*len].damageType);

    printf("Damage value:");
    scanf("%d",&vetWeapons[*len].damageValue);

    printf("Range:");
    scanf("%f",&vetWeapons[*len].range);

    printf("Weigth:");
    scanf("%f",&vetWeapons[*len].weigth);

    vetWeapons[*len].level=1;
    vetWeapons[*len].lenRunes=0;

    printf("\n%s was successfully created!\n\n",vetWeapons[*len].name);
    (*len)++;
    return 1;
}

int findWeapon(weapon vetWeapons[], int len, char weaponName[],int print){
    for(int i=0;i<len;i++){
        if(strcmp(vetWeapons[i].name,weaponName)==0){
            return i;
        }
    }
    if(print==1){
        printf("\nThere is no weapon with this name!\n\n");
    }
    return -1;
}

int addWeaponToCharacter(weapon vetWeapons[], character vetCharacters[], int indexWeapon, int indexCharacter){
    if(vetCharacters[indexCharacter].lenCharWeapons<2){
        for(int i=0;i<vetCharacters[indexCharacter].lenCharWeapons;i++){
            if(strcmp(vetCharacters[indexCharacter].charWeapons[i].name,vetWeapons[indexWeapon].name)==0){
            printf("\n%s has already equipped %s\n\n",vetCharacters[indexCharacter].name,vetWeapons[indexWeapon].name);
            return -1;
            }
        }

        vetCharacters[indexCharacter].charWeapons[vetCharacters[indexCharacter].lenCharWeapons]=vetWeapons[indexWeapon];
        (vetCharacters[indexCharacter].lenCharWeapons)++;
        printf("\n%s was successfully added to %s's inventory!\n\n",vetWeapons[indexWeapon].name,vetCharacters[indexCharacter].name);
        return 1;
    }
    printf("\nCharacter inventory is full!\n\n");
    return -1;
}

int removeWeaponFromCharacter(weapon vetWeapons[], character vetCharacters[], int indexWeapon, int indexCharacter){
    for(int i=0;i<vetCharacters[indexCharacter].lenCharWeapons;i++){
        if(strcmp(vetWeapons[indexWeapon].name,vetCharacters[indexCharacter].charWeapons[i].name)==0){
            for(int j=i;j<(vetCharacters[indexCharacter].lenCharWeapons)-1;j++){
                vetCharacters[indexCharacter].charWeapons[j]=vetCharacters[indexCharacter].charWeapons[j+1];
            }
            printf("\n%s was removed from %s inventory.\n\n",vetWeapons[indexWeapon].name,vetCharacters[indexCharacter].name);
            (vetCharacters[indexCharacter].lenCharWeapons)--;
            return 1;
        }
    }
    printf("\n%s was already not in %s inventory.\n\n",vetCharacters[indexCharacter].name,vetWeapons[indexWeapon].name);
    return -1;
}

float validateRuneCode(float code){
    if(code>=1 && code<4.95){
        float codeF = roundf(code*10)/10;
        return codeF;
    }
    printf("The rune code must be a number between 1 and 4.9");
    return -1;
}

int createRune(rune vetRunes[],int *lenRunes){
    printf("Rune code:");
    float runeCode;
    scanf("%f",&runeCode);
    runeCode = validateRuneCode(runeCode);
    if(runeCode==-1){
        return -1;
    }
    vetRunes[*lenRunes].code = runeCode;

    char testName[32];
    getName(testName,"Rune");
    if(findRune(vetRunes,lenRunes,testName,0)!=-1){
        printf("\nA rune with this name already exists!\n\n");
        return -1;
    }
    strcpy(vetRunes[*lenRunes].name,testName);

    vetRunes[*lenRunes].level = 1;

    printf("\nRune was successfully created!\n\n");
    (*lenRunes)++;
    return 1;
}

int findRune(rune vetRunes[], int len, char runeName[], int print){
    for(int i=0;i<len;i++){
        if(strcmp(vetRunes[i].name,runeName)==0){
            return i;
        }
    }
    if(print==1){
        printf("\nThere is no rune with this name!\n\n");
    }
    return -1;
    
}

void showParty(character vetParty[],int len){
    printf("\n\n----------Party----------\n\n");
    for(int i=0;i<len;i++){
        printf("##### Character %d #####\n\n",i+1);
        printf("Name: %s\n",vetParty[i].name);
        printf("HP: %d\n",vetParty[i].hp);
        printf("Stength: %d\n",vetParty[i].strength);
        printf("Speed: %d\n",vetParty[i].speed);
        printf("Level: %d\n",vetParty[i].level);
        printf("Weapons: ");
        if(vetParty[i].lenCharWeapons!=0){
            for(int j=0;j<vetParty[i].lenCharWeapons;j++){
                printf("%s ||",vetParty[i].charWeapons[j].name);
            }
        }
        printf("\n\n");
    }
}

void showCharacters(character vetCharacters[],int len){
    printf("\n\n----------All Characters----------\n\n");
    for(int i=0;i<len;i++){
            printf("##### Character %d #####\n\n",i+1);
        printf("Name: %s\n",vetCharacters[i].name);
        printf("HP: %d\n",vetCharacters[i].hp);
        printf("Stength: %d\n",vetCharacters[i].strength);
        printf("Speed: %d\n",vetCharacters[i].speed);
        printf("Level: %d\n",vetCharacters[i].level);
        printf("Weapons: ");
        if(vetCharacters[i].lenCharWeapons!=0){
            for(int j=0;j<vetCharacters[i].lenCharWeapons;j++){
                printf("%s ||",vetCharacters[i].charWeapons[j].name);
            }
        }
        printf("\n\n");
    }
}

int main(){
    weapon *weapons = malloc(sizeof(weapon)*20);
    rune *runes = malloc(sizeof(runes)*80);
    character *characters = malloc(sizeof(character)*10);
    character *party  = malloc(sizeof(character)*4);
    int option=0,lenWeapons=0,lenRunes=0,lenCharacters=0,lenParty=0;

    while(option!=-1){
        printf("1- Create character\n");
        printf("2- Add to party\n");
        printf("3- Remove from party\n");
        printf("4- Create weapon\n");
        printf("5- Add weapon to character\n");
        printf("6- Remove weapon from character\n");
        printf("7- Create rune\n");
        printf("8- Add rune to weapon (UNAVAILABLE)\n");
        printf("9- Remove rune from weapon (UNAVAILABLE)\n");
        printf("10- Delete chracter (UNAVAILABLE)\n");
        printf("11- Delete weapon (UNAVAILABLE)\n");
        printf("12- Delete rune (UNAVAILABLE)\n");
        printf("13- Show party\n");
        printf("14- Show characters\n");
        printf("15- Show weapons (UNAVAILABLE)\n");
        printf("16- Show runes (UNAVAILABLE)\n");
        printf("\nChoose an option:");
        scanf("%d",&option);
        bufferCleaner();

        if(option==1){
            createCharacter(characters,&lenCharacters);
        }else if(option==2){
            char name[32];
            getName(name,"Character");
            int index = findCharacter(characters,lenCharacters,name,1);
            if(index!=-1){
                addToParty(party,characters,&lenParty,index);
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

        }else if(option==9){

        }else if(option==10){
        
        }else if(option==11){

        }else if(option==12){

        }else if(option==13){
            showParty(party,lenParty);
        }else if(option==14){
            showCharacters(characters,lenCharacters);
        }else if(option==15){

        }else if(option==16){

        }
    }

    free(weapons);
    free(runes);
    free(characters);
    free(party);
    return 0;
}