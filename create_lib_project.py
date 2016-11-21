import os
import string
import shutil
import glob
from distutils.dir_util import copy_tree





project_name_C = raw_input("Enter lib name(ex: AdMob): ")
project_name = project_name_C.lower()
project_name_U = project_name.upper()

print "Debug " + project_name_C + " " + project_name + " " + project_name_U

#"C:/work/oxygine/academia/"
dest_dir = raw_input("Enter lib dir: ")
tempalte_dir = "oxygine-{{project}}"

def quote(qstr):
    return "{{" + qstr + "}}"

def replace_all(src_str):
    global  project_name
    global  project_name_U
    global  project_name_C

    res_str = src_str.replace(quote("Project"), project_name_C)
    res_str = res_str.replace(quote("project"), project_name)
    return res_str.replace(quote("PROJECT"), project_name_U)

def replace_in_file(name):
    lines = []
    print "reading ", name
    with open(name) as infile:
        for line in infile:
            lines.append(replace_all(line))
    print "writting ", name
    with open(name, 'w') as outfile:
        for line in lines:
            outfile.write(line)

def rename(name):
    new_filename = replace_all(name)
    if new_filename != name:
        print "renamed: ", os.path.basename(name), " to ", os.path.basename(new_filename)
        os.rename(name, os.path.join(os.path.dirname(name), new_filename))

def rename_all(start):
    for root, directories, filenames in os.walk(start):
        for directory in directories:
            rename(os.path.join(root, directory))
    for root, directories, filenames in os.walk(start):
        for filename in filenames:
            fname = os.path.join(root, filename)
            replace_in_file(fname)
            rename(fname)

if __name__ == "__main__":
    #project_name = raw_input('Input project name(ex: facebook): ')
    #dest_dir = raw_input('Input project path(ex: C:\\work\\): ')
    #project_name_C = string.capwords(project_name)
    project_name_U = project_name.upper()

    if not os.path.isdir(dest_dir):
        os.mkdir(dest_dir)

    full_path = dest_dir + replace_all(tempalte_dir)
    print "Copy files to ", full_path

    copy_tree(tempalte_dir + "/", full_path)

    rename_all(full_path)

