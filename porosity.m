function poros = porosity(X) 
	total_tissue_volume = slice_tissue_volume(X(1),X(4),X(7)) + slice_tissue_volume(X(2),X(5),X(7)) + slice_tissue_volume(X(3),X(6),X(7));
	poros = total_tissue_volume./27;
end