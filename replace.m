function [content_modified, replace_success] = replace(content, old, new)
% Replace first occurrence of string old by string new in string array
% content.
    position = strfind(content,old);
    if ~isempty(position)        
        content_modified = strcat(content(1:position(1)-1), new, ...
            content(position(1)+length(old):length(content))); %combine all
            %these together  
            replace_success = true;
    else
        replace_success = false;
        content_modified = content;%if it didn't find the old value 
        %and changed nothing,write the old content again   
       
    end
end
