#/bin/sh

incdir="/usr/local/include/kadare"

if [ ! -e ${incdir} ]; then
	sudo mkdir ${incdir}
fi

cp ./include/kadare/*.hpp ${incdir}
echo "Installation done."
