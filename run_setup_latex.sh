#!/bin/bash

mytexcl=texyise

texmfhome=$(kpsewhich -var-value TEXMFHOME)

echo Your texmf home i s here: $texmfhome

target_folder=$texmfhome/tex/latex/$mytexcl

if [-d $target_folder]; then
    echo "The folder $target_folder already exists"
else
    echo "The folder $target_folder does not exist"
    echo "Creating the folder $target_folder"
    mkdir -p $target_folder
fi

echo "Copying the files to $target_folder"
cp templates/* $target_folder

echo "Running mktexlsr"
mktexlsr $texmfhome