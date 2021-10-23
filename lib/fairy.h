#pragma once

#include <stddef.h>
#include <stdio.h>
#include <elf.h>

#include "vc_vector/vc_vector.h"

#define FAIRY_DEF_STRING(prefix, x) \
    { prefix##_##x, #x }


typedef Elf32_Ehdr FairyFileHeader;
typedef Elf32_Shdr FairySecHeader;
typedef Elf32_Sym FairySym;
typedef Elf32_Rel FairyRel;

typedef struct {
    int define;
    const char* string;
} FairyDefineString;

typedef struct {
    void* sectionData;
    size_t sectionSize;
} FairySectionInfo;

typedef struct {
    FairySectionInfo symtabInfo;
    char* strtab;
    size_t progBitsSizes[3];
    vc_vector* progBitsSections;
    FairySectionInfo relocTablesInfo[3];
} FairyFileInfo;

typedef enum {
    FAIRY_SECTION_TEXT,
    FAIRY_SECTION_DATA,
    FAIRY_SECTION_RODATA,
    FAIRY_SECTION_OTHER //,
} FairySection;

const char* Fairy_StringFromDefine(const FairyDefineString* dict, int define);

FairyFileHeader* Fairy_ReadFileHeader(FairyFileHeader* header, FILE* file);
FairySecHeader* Fairy_ReadSectionTable(FairySecHeader* sectionTable, FILE* file, size_t tableOffset, size_t number);
char* Fairy_ReadStringTable(char* stringTable, FILE* file, size_t tableOffset, size_t tableSize);
FairyRel* Fairy_ReadRelocs(FairyRel* relocTable, FILE* file, size_t offset, size_t number);

void Fairy_InitFile(FairyFileInfo* fileInfo, FILE* file);
void Fairy_DestroyFile(FairyFileInfo* fileInfo);

void Fairy_PrintSymbolTable(FILE* inputFile);

void Fairy_PrintRelocs(FILE* inputFile);
void Fairy_PrintSectionTable(FILE* inputFile);

void PrintZeldaReloc(FILE* file);
