#!/usr/bin/env bash

if [ -f .env ]
then
  export $(cat .env | xargs)
fi

is_package_installed() {
  PACKAGE=$1;
  IS_INSTALL=$(dpkg-query -W --showformat='${Status}\n' $PACKAGE | grep "install ok installed")
  echo $(if [ "$IS_INSTALL" = "install ok installed" ]; then echo "yes"; else echo "no"; fi)
}

install_packages () {
  DEPENDENCIES=(avrdude)
  for i in "${DEPENDENCIES[@]}"; do
    if [ "$(is_package_installed $i)" = "no" ]; then
      echo $i
      sudo apt install -y $i
    fi
  done
}

echo "Install needed packages"
install_packages
