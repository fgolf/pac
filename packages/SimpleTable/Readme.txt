CTable.h handles generating a table on the terminal
it can take strings, floats, and ints for now as inputs (until some enterprising individual overloads the functions).

INSTALL:
Run make to create libSimpleTable.so

in root:
root [0] .L libSimpleTable.so 
root [1] .x test.cpp+
Info in <TUnixSystem::ACLiC>: creating shared library /Users/rwk7t/temp/.rootbuild//Users/rwk7t/Development/pac/externals/source/SimpleTable/./test_cpp.so
+----------------------------------------------------------------+
| Table Title                                                    |
+----------------------------------------------------------------+

                                                               r   
                                                               e   
                                                               a   
                                                               l   
                                                               l   
                                                               y   
                                                                   
                                                               l   
                                                               o   
                        c                                      n   
                        o                                      g   
                        l                                          
                        u                                      l   
                        m                                      a   
                        n                                      b   
                                                               e   
       |      |         1 |      |           |                 l | 
------------------------------------------------------------------
 row 1 | a    | 3         |      | 60.321232 |                   | 
------------------------------------------------------------------
       |      | abcdefghi |      |           |                   | 
------------------------------------------------------------------
       |      |           |      |           |                   | 
------------------------------------------------------------------
       |      |           |      |           |                   | 
------------------------------------------------------------------
       |      |           |      |           |                   | 
------------------------------------------------------------------
 row 4 |      |           |      |           |                   | 
------------------------------------------------------------------

CTable::setCells() - to fill all the cells in a table (supports up to 10 columns right now)

     |      |      |      | 
     | v11  | v12  | v13  | 
     | v21  | v22  | v23  | 
     | v31  | v32  | v33  | 


CTable::setTable() - to fill all the columns, rows, and cells in a table (supports up to 10 columns right now)

       | col 1 | col 2 | col 3 | 
 row 1 | v11   | v12   | v13   | 
 row 2 | v21   | v22   | v23   | 
 row 3 | v31   | v32   | v33   | 


CTable::setCells() - large table (any number of rows; supports up to 10 columns right now)

     |      |      |      |      |      |      |      |      |      |      | 
     | v00  | v01  | v02  | v03  | v04  | v05  | v06  | v07  | v08  | v09  | 
     | v10  | v11  | v12  | v13  | v14  | v15  | v16  | v17  | v18  | v19  | 
     | v20  | v21  | v22  | v23  | v24  | v25  | v26  | v27  | v28  | v29  | 
     | v40  | v41  | v42  | v43  | v44  | v45  | v46  | v47  | v48  | v49  | 
     | v50  | v51  | v52  | v53  | v54  | v55  | v56  | v57  | v58  | v59  | 
     | v60  | v61  | v62  | v63  | v64  | v65  | v66  | v67  | v68  | v69  | 
     | v70  | v71  | v72  | v73  | v74  | v75  | v76  | v77  | v78  | v79  | 
     | v80  | v81  | v82  | v83  | v84  | v85  | v86  | v87  | v88  | v89  | 
     | v90  | v91  | v92  | v93  | v94  | v95  | v96  | v97  | v98  | v99  | 
     | v100 | v101 | v102 | v103 | v104 | v105 | v106 | v107 | v108 | v109 | 
     | v110 | v111 | v112 | v113 | v114 | v115 | v116 | v117 | v118 | v119 | 
     | v120 | v121 | v122 | v123 | v124 | v125 | v126 | v127 | v128 | v129 | 
     | v130 | v131 | v132 | v133 | v134 | v135 | v136 | v137 | v138 | v139 | 
     | v140 | v141 | v142 | v143 | v144 | v145 | v146 | v147 | v148 | v149 | 
     | v150 | v151 | v152 | v153 | v154 | v155 | v156 | v157 | v158 | v159 | 


CTable::setTable() - large table with columns and row labels (any number of rows; supports up to 10 columns right now)

        | col 0 | col 1 | col 2 | col 3 | col 4 | col 5 | col 6 | col 7 | col 8 | col 9 | 
 row 0  | v00   | v01   | v02   | v03   | v04   | v05   | v06   | v07   | v08   | v09   | 
 row 1  | v10   | v11   | v12   | v13   | v14   | v15   | v16   | v17   | v18   | v19   | 
 row 2  | v20   | v21   | v22   | v23   | v24   | v25   | v26   | v27   | v28   | v29   | 
 row 4  | v40   | v41   | v42   | v43   | v44   | v45   | v46   | v47   | v48   | v49   | 
 row 5  | v50   | v51   | v52   | v53   | v54   | v55   | v56   | v57   | v58   | v59   | 
 row 6  | v60   | v61   | v62   | v63   | v64   | v65   | v66   | v67   | v68   | v69   | 
 row 7  | v70   | v71   | v72   | v73   | v74   | v75   | v76   | v77   | v78   | v79   | 
 row 8  | v80   | v81   | v82   | v83   | v84   | v85   | v86   | v87   | v88   | v89   | 
 row 9  | v90   | v91   | v92   | v93   | v94   | v95   | v96   | v97   | v98   | v99   | 
 row 10 | v100  | v101  | v102  | v103  | v104  | v105  | v106  | v107  | v108  | v109  | 
 row 11 | v110  | v111  | v112  | v113  | v114  | v115  | v116  | v117  | v118  | v119  | 
 row 12 | v120  | v121  | v122  | v123  | v124  | v125  | v126  | v127  | v128  | v129  | 
 row 13 | v130  | v131  | v132  | v133  | v134  | v135  | v136  | v137  | v138  | v139  | 
 row 14 | v140  | v141  | v142  | v143  | v144  | v145  | v146  | v147  | v148  | v149  | 
 row 15 | v150  | v151  | v152  | v153  | v154  | v155  | v156  | v157  | v158  | v159  | 


CTable::setTable() - mixed types of cells (any number of rows; supports up to 10 columns right now)

+-----------------------------------------------------------------------------------------------+
| test with heterogenous types                                                                  |
+-----------------------------------------------------------------------------------------------+

        | decimal |  int | string literal | TSring | std::string |              CNumBase<float> | 
 row 0  | 0.1     | 0    | v0             | v04    | v05         | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 1  | 1.1     | 1    | v1             | v14    | v15         | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 2  | 2.1     | 2    | v2             | v24    | v25         | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 4  | 4.1     | 4    | v4             | v44    | v45         | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 5  | 5.1     | 5    | v5             | v54    | v55         | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 6  | 6.1     | 6    | v6             | v64    | v65         | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 7  | 7.1     | 7    | v7             | v74    | v75         | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 8  | 8.1     | 8    | v8             | v84    | v85         | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 9  | 9.1     | 9    | v9             | v94    | v95         | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 10 | 10.1    | 10   | v10            | v104   | v105        | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 11 | 11.1    | 11   | v11            | v114   | v115        | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 12 | 12.1    | 12   | v12            | v124   | v125        | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 13 | 13.1    | 13   | v13            | v134   | v135        | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 14 | 14.1    | 14   | v14            | v144   | v145        | 1.0000$\pm$2.0000$\pm$3.0000 | 
 row 15 | 15.1    | 15   | v15            | v154   | v155        | 1.0000$\pm$2.0000$\pm$3.0000 | 


USAGE:

   CTable table;
   table.useLines(); //will place horizontal lines between rows, recommended, use false to remove them
   table.useTitle(); //will print a title above the table, use false to remove it
   table.useVertColLabels(); //will print the column labels vertically to save space if labels long
			     //or a lot of columns
   table.setPrecision(6); //sets the precision of the floating point entries, default is 4
   string title="Table Title"; 
   table.setTitle(title);

   int i1=3;
   float f1=60.32123;
   string s1="a";
   string s2="abcdefghi";
   //use setCell(entry,row #,column #) to add elements
   //indexing starts at 0,0
   //if a cell exists it is overwritten, and if it does not, the table resized
   table.setCell(s1,0,0);
   table.setCell(s2,1,1);
   table.setCell(i1,0,1);
   table.setCell(f1,0,3);

   string l1="row 1";
   string l2="row 4";
   string l3="column 1";
   string l4="really long label";
   //use setRowLabel(label,row #) and setColLabel to set the labels for row and column respectively
   //indexing starts at 0
   //if a row or column exists, it's label is overwritten, if it does not the table is resized
   table.setRowLabel(l1,0);
   table.setRowLabel(l2,5);
   table.setColLabel(l3,1);
   table.setColLabel(l4,4);

   //prints the full table
   //for now, column labels are printed vertically
   table.print(); //if no argument, print to command line, if argument save to file specified in argument

    // To set all the cells at once (only 10 columns supported, if someone needs more, it is easily extended)
    table.setCells() ( "v11", "v12", "v13")
                     ( "v21", "v22", "v23")
                     ( "v31", "v32", "v33");

    // To set all the row/column titles and cell values at once (only 10 columns supported, if someone needs more, it is easily extended)
    table.etTable() (          "col 1", "col 2", "col 3")
                    ( "row 1",   "v11",   "v12",   "v13")
                    ( "row 2",   "v21",   "v22",   "v23")
                    ( "row 3",   "v31",   "v32",   "v33");
