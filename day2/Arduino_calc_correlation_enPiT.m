pkg load image;
startCpuT = cputime;
exist wv_Ave;

%---------- 1. �������� ----------
N_pt=3129;				% �|�C���g����ݒ�@�@      ���T���v�����ɉ����ĕύX
N_dt=100; 			% �Í����̐���ݒ�@�@  ������g�`�̐�
N_Ave =10;			%�A�x���[�W���O��

o_fid = 'C:\Users\yuuki\source\enpitSecB\day2\4th\PowerModel\Byte1'; 		% enPiT_enshuF\Day2\data\ �̒��ɓ����Ă���t�H���_����(�r���܂ł�)�t�@�C����
PM_fid = 'C:\Users\yuuki\source\enpitSecB\day2\4th\sc-traces-AES\20191226-0001_';	% enPiT_enshuF\Day2\program\octave\PowerModel\ �̒��ɓ����Ă���t�H���_�� Byte����

PM1_f_name = '77DE.txt';      		% .\PowerModel\Byte**����4�̃t�@�C���̖��O�����ɓ����
PM2_f_name = '5447.txt';
PM3_f_name = '9710.txt';
PM4_f_name = 'A714.txt';



%flnm_corr='..\data\Correlation_1026.txt'; % �t�@�C������ݒ�@�@�@�@ �������B���֔g�`�̕ۑ��t�@�C����
%flnm_wvfm = '..\data\WaveForm_1026.txt';
%---------- 1. �������� ----------

%---------- 2. �f�[�^�ǂݍ��� ----------

%---------- �p���[���f�� ----------
PM1 = importdata(strcat(PM_fid,'\',PM1_f_name)); % �p���[���f��
PM2 = importdata(strcat(PM_fid,'\',PM2_f_name)); % �p���[���f��
PM3 = importdata(strcat(PM_fid,'\',PM3_f_name)); % �p���[���f��
PM4 = importdata(strcat(PM_fid,'\',PM4_f_name)); % �p���[���f��
%PM5 = importdata('..\HW\HW_C10_5.txt'); % �p���[���f��
%PM6 = importdata('..\HW\HW_C10_6.txt'); % �p���[���f��
%PM7 = importdata('..\HW\HW_C10_7.txt'); % �p���[���f��
%PM8 = importdata('..\HW\HW_C10_8.txt'); % �p���[���f��
%PM9 = importdata('..\HW\HW_C10_9.txt'); % �p���[���f��
%PM10 = importdata('..\HW\HW_C10_10.txt'); % �p���[���f��
%PM11 = importdata('..\HW\HW_C10_11.txt'); % �p���[���f��
%PM12 = importdata('..\HW\HW_C10_12.txt'); % �p���[���f��
%PM13 = importdata('..\HW\HW_C10_13.txt'); % �p���[���f��
%PM14 = importdata('..\HW\HW_C10_14.txt'); % �p���[���f��
%PM15 = importdata('..\HW\HW_C10_15.txt'); % �p���[���f��
%PM16 = importdata('..\HW\HW_C10_16.txt'); % �p���[���f��
%---------- �p���[���f�� ----------

for a = 1:1
  if ans == 1
    break;
  end
  %---------- �g�` ----------
  for dt = 1:N_dt*N_Ave

      if dt < 10
          str_dt = num2str(dt);
          str_dt = strcat('000',str_dt);
      end

      if dt >= 10 && dt <100
          str_dt = num2str(dt);
          str_dt = strcat('00',str_dt);
      end

      if dt >= 100 && dt <1000
          str_dt = num2str(dt);
          str_dt = strcat('0',str_dt);
      end

      if dt >= 1000
          str_dt = num2str(dt);
  %         str_dt = strcat('0',str_dt);
      end

      wv(dt,:) = dlmread(strcat(o_fid,str_dt,'.txt'),'\t',[3 2 N_pt+2 2]);

  end
  %---------- �g�` ----------
  %---------- 2. �f�[�^�ǂݍ��� ----------

  %----------�A�x���[�W���O-----------
  dt = 1;
  wv_Ave = zeros(N_dt,N_pt);
  while dt <= N_dt
      for Ave = 1:N_Ave
          wv_Ave(dt,:) = wv_Ave(dt,:) + wv((dt-1)*N_Ave + Ave,:);
      end
      wv_Ave(dt,:) = wv_Ave(dt,:)./N_Ave;
      dt=dt+1;
  end

end


%---------- ���֌W���v�Z ----------
corr_time = zeros(N_pt,1);

for pt = 1:N_pt

    corr_time(pt,1)=corr2(wv_Ave(1:N_dt,pt),PM1(1:N_dt,1));
    corr_time(pt,2)=corr2(wv_Ave(1:N_dt,pt),PM2(1:N_dt,1));
    corr_time(pt,3)=corr2(wv_Ave(1:N_dt,pt),PM3(1:N_dt,1));
    corr_time(pt,4)=corr2(wv_Ave(1:N_dt,pt),PM4(1:N_dt,1));
%    corr_time(pt,5)=corr2(wv_Ave(1:N_dt,pt),PM5(1:N_dt,1));
%    corr_time(pt,6)=corr2(wv_Ave(1:N_dt,pt),PM6(1:N_dt,1));
%    corr_time(pt,7)=corr2(wv_Ave(1:N_dt,pt),PM7(1:N_dt,1));
%    corr_time(pt,8)=corr2(wv_Ave(1:N_dt,pt),PM8(1:N_dt,1));
%    corr_time(pt,9)=corr2(wv_Ave(1:N_dt,pt),PM9(1:N_dt,1));
%    corr_time(pt,10)=corr2(wv_Ave(1:N_dt,pt),PM10(1:N_dt,1));
%    corr_time(pt,11)=corr2(wv_Ave(1:N_dt,pt),PM11(1:N_dt,1));
%    corr_time(pt,12)=corr2(wv_Ave(1:N_dt,pt),PM12(1:N_dt,1));
%    corr_time(pt,13)=corr2(wv_Ave(1:N_dt,pt),PM13(1:N_dt,1));
%    corr_time(pt,14)=corr2(wv_Ave(1:N_dt,pt),PM14(1:N_dt,1));
%    corr_time(pt,15)=corr2(wv_Ave(1:N_dt,pt),PM15(1:N_dt,1));
%    corr_time(pt,16)=corr2(wv_Ave(1:N_dt,pt),PM16(1:N_dt,1));

end
%---------- ���֌W���v�Z ----------


%---------- ���֌W���o�� ----------
%---------- �O���t ----------
x = 1:N_pt;
plot(x,corr_time(:,1),x,corr_time(:,2),x,corr_time(:,3),x,corr_time(:,4));
legend(PM1_f_name,PM2_f_name,PM3_f_name,PM4_f_name);
%---------- �O���t ----------
%---------- 3. �t�@�C�� ----------
%wvform(:,1) = wv_Ave(1,:);
%save(flnm_wvfm, 'wvform', '-ascii');
%save(flnm_corr, 'corr_time', '-ascii');
%


%---------- 3. �t�@�C�� ----------
%---------- ���֌W���o�� ----------
ntime = cputime-startCpuT;
nhour = floor(ntime/60/60);
nmin = floor((ntime-nhour*3600)/60);
nsec = ntime-nhour*3600-nmin*60;
printf('%d%s%02d%s%04.1f%s\n',nhour,'h',nmin,'m',nsec,'s');
