clear all;
close all;

tic;

clear all;
close all;

simulations = zeros();
counter = 0;

for X1 = 0.15:0.05:0.9
	for X3 = 0.1:0.05:0.9
		X2 = X1;
		p = porosity([X1,X1,X1,X2,X2,X2,X3]);
		disp([X1,X2,X3,p])
		if p > 0.5
			counter = counter+1;
			simulations(counter,1) = X1;
			simulations(counter,2) = X2;
			simulations(counter,3) = X3;
			simulations(counter,4) = p;
			simulations(counter,5) = problem_function([X1,X1,X1,X2,X2,X2,X3]);
		end
	end
end

toc;