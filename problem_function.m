function obj = problem_function(X)
  format long;
  
  % Read and modify Python script for Abaqus
  file =fopen('Python_original_script.py');
  C=textscan(file,'%s','delimiter','\n');
  fclose(file);

  C = modify_content(C,'MAGIC00',num2str(1.0+X(1)/2));  
  C = modify_content(C,'MAGIC01',num2str(1.0-X(1)/2));  
  C = modify_content(C,'MAGIC02',num2str(1.0+X(2)/2));  
  C = modify_content(C,'MAGIC03',num2str(X(2)/2));  
  C = modify_content(C,'MAGIC04',num2str(1.0-X(2)/2));  
  C = modify_content(C,'MAGIC05',num2str(1.0+X(3)/2));  
  C = modify_content(C,'MAGIC06',num2str(1.0-X(3)/2));  
  C = modify_content(C,'MAGIC07',num2str(1.0+X(4)/2));  
  C = modify_content(C,'MAGIC08',num2str(1.0-X(4)/2));  
  C = modify_content(C,'MAGIC09',num2str(1.0+X(5)/2));  
  C = modify_content(C,'MAGIC10',num2str(X(5)/2));  
  C = modify_content(C,'MAGIC11',num2str(1.0-X(5)/2));  
  C = modify_content(C,'MAGIC12',num2str(1.0+X(6)/2));  
  C = modify_content(C,'MAGIC13',num2str(1.0-X(6)/2));  
  C = modify_content(C,'MAGIC14',num2str(1.0+X(7)/2));  
  C = modify_content(C,'MAGIC15',num2str(1.0-X(7)/2));  
  
  % Print new file
  new_pythonfile = fopen('Python_script.py','w');  % Open the file
  for k=1:numel(C{1}) 
    fprintf(new_pythonfile,'%s\n',char(C{1}{k})); 
  end
  fclose(new_pythonfile);

  % Python script -> inp file
  [status,result]=dos('abq2018 cae noGui=Python_script.py','-echo'); 
  if status~=0 % Stop the loop and return an error message
      error('Abaqus CAE error');
      return;  
  end
  
  % Launch C++ bone regeneration code
  [status,result]=dos('cubic_scaffold.exe','-echo'); 
  if status~=0 % Stop the loop and return an error message
      error('C++ regeneration code error');
      return; 
  end
  
  % Read result (objective)
  obj = 1-readoutput('out.info');
  disp(obj);
  
  % Write input and objective to log file
  fid = fopen('optimisation.log', 'a');
  fprintf(fid, '%d %d %d %d %d %d %d ', X);
  fprintf(fid, '%d\n', obj);
  fclose(fid);
end