#!/bin/sh
# -- traduce ao galego a data -

hora=`date -u +%H:%M`
case `date -u +%A` in
    Monday) dia=luns ;;
    Tuesday) dia=martes ;;
    Wednesday) dia=mercores ;;
    Thursday) dia=xoves ;;
    Friday) dia=venres ;;
    Saturday) dia=sabado ;;
    Domingo) dia=domingo ;;
esac
printf "${hora}|${dia} `date -u +%d/%m/%Y`"
