%opção 1-- receber Meta Teds
%opção 2-- receber Teds do canal 1 (acelerometro eixo x)
%opção 3-- receber Teds do canal 2 (acelerometro eixo y)
%opção 4-- receber Teds do canal 3 (acelerometro eixo z)
%opção 5-- receber Teds do canal 4 (atuador)
%opção 6-- pedir um valor do canal 1 - eixo x
%opção 7-- pedir um valor do canal 2 - eixo y
%opção 8-- pedir um valor do canal 3 - eixo z
%opção 9-- envia 

function [val, successFlag] = Comandos_STIM(op)
    
    %op = input('Escolha uma opção: ');

    STIM = serialport("COM9", 9600); %nome da porta série e baund rate
    

    %arrays criados para o NCAP pedir à STIM: Meta Teds, Teds dos canais os valores de cada canal
    array_1 = [0 0 1 2 0 2 1 0]; %ler Meta Teds
    array_2 = [0 1 1 2 0 2 3 0]; %ler canal 1 Teds(acelerometro eixo x)
    array_3 = [0 2 1 2 0 2 3 0]; %ler canal 2 Teds (acelerometro eixo y)
    array_4 = [0 3 1 2 0 2 3 0]; %ler canal 3 Teds (acelerometro eixo z)
    array_5 = [0 4 1 2 0 2 3 0]; %ler canal 4 Teds (atuador)
    array_6 = [0 1 3 1 0 1 0]; % ler valores do canal 1-x
    array_7 = [0 2 3 1 0 1 0]; % ler valores do canal 2-y
    array_8 = [0 3 3 1 0 1 0]; % ler valores do canal 3-z
    array_9 = [0 4 3 2 0 2 0 1]; %ler canal 4 (atuador)

    
    g=9.8;
    sensi=0.800;

    if (op==1)
     %opção 1 --  pedir e receber Meta TEDS
      write(STIM,array_1,"uint8");  %comando para pedir ao STIM para enviar a Meta TEDS
      response = read(STIM,3,"uint8"); %ler resposta da STIM

      if (response(1)==0) %se na posição 1 for 0--fail flag
           disp("Ocorreu um erro na receção das Meta TEDS"); %mostrar mensagem de erro
           successFlag=0; 
      else
          val=[read(STIM,response(3),"uint8")]; %criar a variável val para posteriormente fazer o display dos valores pretendidos enviados pela stim
          successFlag=1;
      end

    elseif (op==2)
    %opção 2 -- pedir e receber Teds do canal 1
        write(STIM,array_2,"uint8");  %comando para pedir ao STIM para enviar Teds do canal 1
        response= read(STIM,3,"uint8"); %ler resposta da STIM
        if response(1)==0 %se o valor da posição 1 for 0 ocorreu um erro e é mostrada uma mensagem de erro (fail flag)
           disp("Ocorreu um erro na receção das Teds"); %mostrar mensagem de erro
           successFlag=0; %a operação não foi bem sucedida
        else 
           val=read(STIM,response(3),"uint8");  %criar a variável val para posteriormente fazer o display dos valores pretendidos enviados pela STIM
           successFlag=1;
        end

     elseif (op==3)
     %opção 3-- pedir e receber teds do canal 2
        write(STIM,array_3,"uint8");  %comando para pedir ao STIM para enviar Teds do canal 2
        response= read(STIM,3,"uint8"); %ler resposta da STIM
        disp(response);
        if response(1)==0 %se o valor da posição 1 for 0 ocorreu um erro e é mostrada uma mensagem de erro (fail flag)
           disp("Ocorreu um erro na receção das Teds"); %mostrar mensagem de erro
           successFlag=0; 
        else
           val=read(STIM,response(3),"uint8");  %criar a variável val para posteriormente fazer o display dos valores pretendidos enviados pela stim

        end

    elseif (op==4)
    %opção 4-- pedir e receber Teds do canal 3
        write(STIM,array_4,"uint8");  %comando para pedir ao STIM para enviar Teds do canal 4
        response= read(STIM,3,"uint8"); %ler resposta da STIM
        disp(response);
        if response(1)==0 %se o valor da posição 1 for 0 ocorreu um erro e é mostrada uma mensagem de erro (fail flag)
           disp("Ocorreu um erro na receção das Teds"); %mostrar mensagem de erro
           successFlag=0; 
        else
           val=read(STIM,response(3),"uint8"); %a variável val armazena os valores enviados pela STIM
           successFlag=1;
        end 

    elseif (op==5)
    %opção 5-- pedir e receber Teds do canal 4 (atuador)
        write(STIM,array_5,"uint8");  %comando para pedir ao STIM para enviar Teds do canal 4
        response= read(STIM,3,"uint8"); %ler resposta da STIM
        disp(response);
        if response(1)==0 %se o valor da posição 1 for 0 ocorreu um erro e é mostrada uma mensagem de erro (fail flag)
           disp("Ocorreu um erro na receção das Teds"); %mostrar mensagem de erro
           successFlag=0; 
        else
           val=read(STIM,response(3),"uint8"); %a variável val armazena os valores enviados pela STIM
           successFlag=1;
        end


    elseif (op==6)
         %opção 6 (Ver os valores do sensor canal 1 -> x)
          tic
          write(STIM,array_6,"uint8");  %comando para pedir valor do canal 2- eixo y
          response= read(STIM,3,"uint8"); %ler resposta da STIM
       
            if response(1) == 1 %Se tivermos sucess flag
                disp(response)
                disp("Os valores do sensor do Canal 1 são: ")
                valor = read(STIM, response(3), "uint8");
                valor1 = (valor*(5/256)); % valor de tensão = valor decimal * resolução (vdd/2^8)
                val = ((valor1*g)/sensi); % valor de aceleração = (valor1 * gravidade) / sensibilidade do sensor
                disp(val); % cria a variável valor que lê o terceiro elemento que corresponde aos valores a serem enviados pela STIM
                successFlag=1;
                toc;
    
            else
                successFlag=0;
            end
   
    elseif (op==7)
          %opção 7 --pedir um valor do canal 2- eixo y
          tic
          write(STIM,array_7,"uint8");  %comando para pedir valor do canal 2- eixo y
          response= read(STIM,3,"uint8"); %ler resposta da STIM
       
            if response(1) == 1 %Se tivermos sucess flag
                disp(response)
                disp("Os valores do sensor do Canal 2 são: ")
                valor = read(STIM, response(3), "uint8");
                valor1 = (valor*(5/256)); % valor de tensão = valor * resolução (vdd/2^8)
                val = ((valor1*g)/sensi); % valor de aceleração = (valor1 * gravidade) / sensibilidade do sensor
                disp(val); % cria a variável valor que lê o terceiro elemento que corresponde aos valores a serem enviados pela STIM
                successFlag=1;
                toc;
    
            else
                successFlag=0;
            end

    elseif (op==8)
          %opção 8 --pedir um valor do canal 3- eixo z
          tic
          write(STIM,array_8,"uint8");  %comando para pedir valor do canal 2- eixo y
          response= read(STIM,3,"uint8"); %ler resposta da STIM
       
            if response(1) == 1 %Se tivermos sucess flag
                disp(response)
                disp("Os valores do sensor do Canal 3 são: ")
                valor = read(STIM, response(3), "uint8");
                valor1 = (valor*(5/256)); % valor de tensão = valor * resolução (vdd/2^8)
                val = ((valor1*g)/sensi); % valor de aceleração = (valor1 * gravidade) / sensibilidade do sensor
                disp(val); % cria a variável valor que lê o terceiro elemento que corresponde aos valores a serem enviados pela STIM
                successFlag=1;
                toc;
    
            else
                successFlag=0;
            end
           
     elseif (op==9)
          %opção 9 --enviar valor à STIM
          write(STIM,array_9,"uint8");  
          response= read(STIM,3,"uint8"); %ler resposta da STIM
          if response(1) == 1 && response(2)==0 && response(3)==0 %Se tivermos sucess flag
              disp("LED ligado!");
          elseif (response(1)==0)
              disp("Erro!")
          end

    else 
        disp("A opção pretendida não é válida");

    end

clear STIM

end
 