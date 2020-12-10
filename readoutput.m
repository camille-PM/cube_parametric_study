function objective = readoutput(job_file)
    % Open and read C++ output file
    fileID = fopen(job_file,'r'); %reading the output file
    objective = fscanf(fileID,'%f');
    fclose(fileID);
end