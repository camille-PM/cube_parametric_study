function  new_content = modify_content(old_content,old,new)
	counter = 0;
	for k=1:numel(old_content{1})%the whole number of elements in array
		content = old_content{1}{k};
		replace_success = true;
		while (replace_success)
		   [content, replace_success] = replace(content, old, new);   
		   counter = counter+1;
		end 
		new_content{1}{k} = content; 
	end
end