#!/usr/bin/python
#Converte2UTF8("gb2312.txt","./dictionary.dsl")

def ParserDSLLine(line) :
    tag1_start = 1
    tag2_suspend = 2 
    tag2_start = 3 
    value_start = 4 
    content_start = 5
    tag2_end_suspend = 6

    strlen = len(line)
    i = 0
    parse_state = 0

    tag_stack = list() 
    content = list()

    escape = 0 
    match = 0

    tag = ""
    value = ""
    text = ""
    word = ""
    while i < strlen :
        if line[i] == '\\' :
            if escape == 0 :
                escape = 1
                i += 1
                continue

        if parse_state == 0 :
            if escape :
                word += line[i]
            else :
                if line[i] == '[' :
                    parse_state = tag1_start
                elif line[i] == '{' :
                    parse_state = tag2_suspend
                else :
                    word += line[i]
        elif parse_state == tag1_start :
            if escape :
                tag += line[i]
            else :
                if line[i] == ']' :
                    parse_state = content_start
                    #add the item
                    if match :
                        temp = tag_stack[-1]
                        #print("kkkkk######", tag , temp,tag_stack)
                        if temp != {} and temp['name'] == tag :
                            del tag_stack[-1] ;
                        else :
                            print("#####tag doesn't match", tag)
                        match = 0
                    else :
                        tag_stack.append({'name':tag,'attribute':value})

                    tag = ""
                    value = ""
                elif line[i] == ' ':
                    parse_state = value_start
                elif line[i] == '/':
                    match = 1
                else :
                    tag += line[i]
        elif parse_state == value_start :
            if escape :
                value += line[i]
            else :
                if line[i] == ']' :
                    parse_state =  content_start
                    #add the item
                    if match :
                        temp = tag_stack[-1]
                        #print("######", tag , temp,tag_stack)
                        if temp != {} and temp['name'] == tag :
                            del tag_stack[-1] ;
                        else :
                            print("tag doesn't match", tag)
                        match  = 0
                    else :
                        tag_stack.append({'name':tag,'attribute':value})
                    tag = ""
                    value = ""
                else:
                    value += line[i]
        elif parse_state == content_start :
            if escape :
                text += line[i]
            else :
                if line[i] == '[' :
                    parse_state = tag1_start
                    if text != "" :
                        content.append(text)
                        text = ""
                elif line[i] == '{' :
                    parse_state = tag2_suspend
                    if text != "" :
                        content.append(text)
                        text = ""
                else :
                    text += line[i]
        elif parse_state == tag2_suspend :
            if line[i] == '{' :
                parse_state = tag2_start
            else :
                print("parse fail {{{{");
        elif parse_state == tag2_start :
            if escape :
                tag += line[i]
            else :
                if line[i] == '}' :
                    parse_state = tag2_end_suspend
                elif line[i] == '/':
                    match = 1
                else :
                    tag += line[i]
        else :
            if parse_state == tag2_end_suspend : 
                if line[i] == '}' :
                    parse_state = 0
                    #add stack value
                    if match :
                        #print("xxxxxxxxxxxxxxxxxxxx######", tag , temp,tag_stack)
                        temp = tag_stack[-1]
                        if temp != {} and temp['name'] == tag :
                            del tag_stack[-1] ;
                        else :
                            print("tag doesn't match")
                        match  = 0
                    else :
                        tag_stack.append({'name':tag,'attribute':value})
                    tag = ""
                    value = ""
            else :
                print("may be something wrong")
        i += 1
        escape = 0
    #print(tag_stack)
    meaning =""
    for tmp_str in content :
        meaning += tmp_str 
    #print(content)
    print(meaning)
    print(word)


file = open("gb2312.txt",'r')
count = 0
for line in file :
    ParserDSLLine(line)
    if count > 10 :
        break 
    count += 1





""""
def ParseLine(line) :
    tag_stack = list() 
    content = list()
    i = 0
    strlen = len(line)
    while i < strlen :
        tag = ""
        value = ""
        text = ""
        if line[i] == '\\' :
            if escape == 0 :
                escape = 1
            else :
                escape = 1
                if tag_start :
                    tag += line[i]
                elif value_start :
                    value += line[i]
                else:
                    text += line[i]
        elif line[i] == '[' :
            if escape == 1 :
                if tag_start :
                    tag += line[i]
                elif value_start :
                    value += line[i]
                else:
                    text += line[i]
            else:
                if line[i+1] == '/' :
                    tag_start = 1
                    match = 1
                    i += 1
                elif tag_start :
                    if text != "" :
                        content.append(text)
                    tag_start = 0
                else :
                    tag_start = 1
                    value_start = 0

        elif line[i] == ' ' :
                if tag_start :
                    value_start = 1
                    tag_start = 0
                else
                    text += line[i]
        elif line[i] == ']' :
            if escape == 1 :
                if tag_start :
                    tag += line[i]
                elif value_start :
                    value += line[i]
                else:
                    text += line[i]
            else:
                tag_start = 0
                value_start = 0
                if match == 0 :
                    tag_stack.append({'name':tag,'attribute':value})
                else
                    temp = tag_stack[-1]
                    if temp != {} and temp['name'] == tag :
                        del tag_stack[-1] ;
                    else :
                        print("tag doesn't match")
        else :
            if tag_start :
                tag += line[i]
            elif value_start :
                value += line[i]
            else:
                text += line[i]


        if line[i] == '[' :
            i += 1
            tag_ok = 0
            tag_end = 0
            while line[i] != ']' :
                if line[i] == ' ' :
                    tag_ok = 1
                if tag_ok :
                    value += line[i]
                else :
                    tag += line[i]
                i += 1
            if tag_end != 1 :
                tag_stack.append({'name':tag,'attribute':value})
            else:
        i += 1

        while i < strlen and line[i] != ']' and line[i] != '[' :
            text += line[i]
            i += 1
        if text != "" :
            content.append(text)

    if len(tag_stack) :
        print(tag_stack)

    if len(content) :
        print(content)

"""
