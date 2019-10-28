TEMPLATE = subdirs

SUBDIRS += lab1 \
    lab2 \
    lab3 \
    LibQCustomPlot
#qwtplot3d \
lab1.depends = LibQCustomPlot
lab2.depends = LibQCustomPlot
lab3.depends = LibQCustomPlot


