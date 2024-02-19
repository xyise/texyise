#!/bin/bash

if [ $# -eq 0 ]
	then
		echo "'clean' or 'update' is required"
        echo "clean: remove the virtual environment"
        echo "update: update the virtual environment"
		exit
fi


if [ $1 == "clean" ]
    then
        echo "Removing the virtual environment"
        rm -rf venv
        echo "create a new virtual environment"
        python3 -m venv venv
fi  

# Run this after creating a new virtualenv to install the required packages
# See: https://godatadriven.com/blog/a-practical-guide-to-setuptools-and-pyproject-toml/


# activate the virtual environment
source venv/bin/activate

# upgrade pip 
# pip version should be at least 21.3
#   see here: https://stackoverflow.com/questions/69711606/how-to-install-a-package-using-pip-in-editable-mode-with-pyproject-toml
python -m pip install -U pip

mkdir -p python/src

# Install the required packages
# This will install packages listed in setup.cfg
pip install -e .

# Install the packages for development
# This will install packages listed in setup.cfg under [dev-packages]
pip install -e ".[dev]"

# install pre-commit hooks
# With this, we need to create a .pre-commit-config.yaml file
# pre-commit install --hook-type pre-commit --hook-type pre-push