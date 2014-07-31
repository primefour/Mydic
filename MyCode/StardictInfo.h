#ifndef __STARDICT_INFO_H__
#define __STARDICT_INFO_H__
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"File.h"

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
        }
        ~StardictInfo(){
            if(version){
                free(version);
            }
            if(book_name){
                free(book_name);
            }
            if(author){
                free(author);
            }
            if(email){
                free(email);
            }
            if(website){
                free(website);
            }
            if(description){
                free(description);
            }
            if(date){
                free(date);
            }
        }
        int init();
        char *get_version(){
            return version;
        }
        char *get_book_name(){
            return book_name;
        }
        char *get_author(){
            return author;
        }
        char *get_email(){
            return email;
        }
        char *get_website(){
            return website;
        }
        char *get_description(){
            return description;
        }
        char *get_date(){
            return date;
        }
        long get_word_count(){
            return word_count;
        }
        long get_syn_word_count(){
            return syn_word_count;
        }
        long get_idx_file_size(){
            return idx_file_size;
        }
        int get_offset_bits(){
            return  (offset_is_64bit == 64)?64:32;
        }
        char *get_same_types_sequence(){
            return same_types_sequence;
        }
        void dump();
    private:
        char *get_string_value(char *str_line);
        int   get_integer_value(char *str_line);
        void parse_line(char *str_line);
    private:
        char *version;
        char *book_name;
        char *author;
        char *email;
        char *website;
        char *description;
        char *date;
        long word_count;
        long syn_word_count;
        long idx_file_size;
        short offset_is_64bit;
        char *same_types_sequence; 
        File info_file;
};
#endif //
