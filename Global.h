#ifndef GLOBAL_H
#define GLOBAL_H


// Contain enumerators and struct to be seen for all classes

enum DNA_Type{promoter, motif, tail, noncoding};
enum RNA_Type {mRNA, pre_mRNA, mRNA_exon, mRNA_intron};
enum Protein_Type {Hormon, Enzyme, TF, Cellular_Function};


struct Codon
{
  	char value[4];    	    // 4th location for null character
    char AminoAcid;  	    // corresponding AminoAcid according to Table
};

#endif // GLOBAL_H
