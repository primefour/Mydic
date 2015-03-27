#ifndef __STARDICT_INFO_H__
#define __STARDICT_INFO_H__
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"File.h"
#include"memory_test_tool.h"

class StardictInfo{
    public:
        StardictInfo(const char *file_path):info_file(file_path){
            version = NULL;
            book_name = NULL;
            author = NULL;
            email = NULL;
            website = NULL;
            description = NULL;
            date = NULL;
            same_types_sequence = NULL;
        }
        ~StardictInfo(){
        }

        inline String8 getVersion(){
            return version.getStringValue('=');
        }
        inline String8 getBookName(){
            return book_name.getStringValue('=');
        }
        inline String8 getAuthor(){
            return author.getStringValue('=');
        }
        inline String8 getEmail(){
            return email.getStringValue('=');
        }
        inline String8 getWebsite(){
            return website.getStringValue('=');
        }
        inline String8 getDescription(){
            return description.getStringValue('=');
        }
        inline String8 getDate(){
            return data.getStringValue('=');
        }

        inline long get_word_count(){
            String8 value = word_count.getStringValue('=');
            if(value.isEmpty()){
            }
    return atoi(value);
            return word_count;
        }
        inline long get_syn_word_count(){
            return syn_word_count;
        }

        inline long get_idx_file_size(){
            return idx_file_size;
        }

        inline int get_offset_bits(){
            return  (offset_is_64bit == 64)?64:32;
        }

        inline char *get_same_types_sequence(){
            return same_types_sequence;
        }
        void dump();
    private:
        char *get_string_value(char *str_line);
        int   get_integer_value(char *str_line);
        void parse_line(char *str_line);
    private:
        String8 version;
        String8 book_name;
        String8 author;
        String8 email;
        String8 website;
        String8 description;
        String8 date;
        String8 file_name;

        long word_count;
        long syn_word_count;
        long idx_file_size;
        short offset_is_64bit;
        char *same_types_sequence; 
};
#endif //
