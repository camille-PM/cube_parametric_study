function volume = slice_tissue_volume(a1,b1,c1) % a along x axis, b along y axis (both 3 times), c along z axis (9 times)
	[aa] = sort([a1,b1,c1],'descend');
    a = aa(1);
    b = aa(2);
    c = aa(3);
	volume = 9*(a^2 + (b^2+c^2)*(1-a));
end