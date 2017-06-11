%% 仿真:比特流无线传输的(一种)基本过程
% 仿真涉及的主要技术:QAM调制 OFDM 正交调制 MIMO
% 假设信号只受到噪声影响,且只在无线信道中才会有噪声影响

clc;
close all;
clear;

%% 全局参数
QAMbn=2; % QAM调制bit数,2:4QAM,4:16QAM,6:64QAM,8:256QAM
Ntx=4; % MIMO天线数量
Nsr=2^3; % 子载波数量(2,4,8,16...)

Delta_F=312.5e3; % 子载波频率间隔(Hz),同时也是QAM-OFDM符号率
N_fft=2^7; % 用于实现OFDM的fft点数,应大于Nsr

br=Delta_F*QAMbn*Nsr; % 比特率,bps
fs=Delta_F*N_fft; % DAC采样率

%% 原始比特流
bits=randi([0,1],Ntx,QAMbn*Nsr); % 原始比特流
                                 % Ntx行,表示Ntx个Tx Chain
                                 % 每行最终会变成一个QAM-OFDM符号

figure();
for i=1:Ntx
    subplot(Ntx,1,i);
    stairs(0:length(bits),[bits(i,:),bits(i,QAMbn*Nsr)]);
    axis([0,length(bits),-.5,1.5]);
    grid on;
    title(sprintf('Tx Chain %d 原始比特流',i));
    xlabel(sprintf('时间轴(\\times%.1f\\mus)',1e6/br),'interpreter','tex');
end

%% 4QAM
% 下面的一批匿名函数仅仅是为了处理方便,并不代表实际处理方式
qam_resize=@()( reshape(bits.',QAMbn/2,Ntx*Nsr*2).' ); % bits' row vector 变成Ntx*Nsr/2行QAMbn/2列
binarr2num=@(ba)( sum(repmat(2.^(size(ba,2)-1:-1:0),size(ba,1),1).*ba,2) );
adj_num=@(n)(n./(2^(QAMbn/2)-1)*2-1);
num2qam=@(n)(downsample(n.',2,0)+1j*downsample(n.',2,1));
qam_r2m=@(q)( reshape(q,Nsr,Ntx).' ); % 转化成多个Tx Chain传输的矩阵形式

qam=qam_r2m(num2qam(adj_num(binarr2num(qam_resize())))); % 这里的QAM只是星座
% 提示 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% qam是Ntx行,Nsr列的矩阵.其中,每行各自通过一个天线发射出去(MIMO空间复用);
% 每个天线发送时,使用FDM将整行中的各个元素(各列)"并行"发送(OFDM).
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear qam_resize binarr2num adj_num num2qam qam_r2m;

for i=1:Ntx
    figure('NumberTitle', 'off', 'Name', sprintf('Tx Chain %d',i));
    subplot('position',[.058,.59,.4,.33]);
    stairs(0:length(qam(i,:)),real([qam(i,:),qam(i,Nsr)]),'b');
    axis([0,length(qam(i,:)),-1.5,1.5]);
    grid on;
    title('QAM实部');

    subplot('position',[.058,.12,.4,.33]);
    stairs(0:length(qam(i,:)),imag([qam(i,:),qam(i,Nsr)]),'r');
    xlabel(sprintf('时间轴(\\times%.1f\\mus)',1e6/br*QAMbn),'interpreter','tex');
    axis([0,length(qam(i,:)),-1.5,1.5]);
    grid on;
    title('QAM虚部');

    subplot('position',[.6,.12,.35,.8]);
    plot(qam(i,:),'o','markersize',7);
    xlabel('实部');
    ylabel('虚部');
    axis([-1.5,1.5,-1.5,1.5]);
    grid on;
    title('星座(Tx)');
end

%% OFDM-MIMO
% 使用IFFT进行QAM-OFDM
% bb_ofdm_ifft_i=[zeros(Ntx,1), qam(:,Nsr/2+1:Nsr), zeros(Ntx,N_fft-Nsr-1), qam(:,1:Nsr/2)];
% bb_ofdm_ifft_o=ifft(bb_ofdm_ifft_i,N_fft,2);

% "各个子载波分别QAM"方法实现QAM-OFDM,与IFFT方法完全等价
t_ax=0:1/fs:(N_fft-1)/fs;
nsr=[-Nsr/2:-1,1:Nsr/2].'; % 子载波下标
bb=qam*exp(1j*2*pi*Delta_F*nsr*t_ax)./N_fft;

% 显示被调制的各个子载波
for i=1:Ntx
    qam_tmp=qam(i,:);
    bb_tmp=repmat(qam_tmp.',1,N_fft).*exp(1j*2*pi*Delta_F*nsr*t_ax)./N_fft;
    
    figure('NumberTitle', 'off', 'Name', sprintf('Tx Chain %d',i));
    subplot('position',[.1,.59,.4,.33]);
    plot(t_ax.*1e6,real(bb_tmp.'));
    axis([0,N_fft/fs*1e6,-1,1]); axis 'auto y';
    title('OFDM各个子载波实部');
    grid on;
    
    subplot('position',[.1,.12,.4,.33]);
    plot(t_ax.*1e6,imag(bb_tmp.'));
    axis([0,N_fft/fs*1e6,-1,1]); axis 'auto y';
    title('OFDM各个子载波虚部');
    xlabel('时间轴/\mus');
    grid on;
    
    subplot('position',[.62,.12,.35,.8]);
    plot(t_ax.*1e6,real(bb(i,:)));
    hold on;
    plot(t_ax.*1e6,imag(bb(i,:)));
    hold off;
    axis([0,N_fft/fs*1e6,-1,1]); axis 'auto y';
    title('OFDM各子载波和');
    legend('实部','虚部','Location','SouthEast');
    xlabel('时间轴/\mus');
    grid on;
end

clear nsr bb_tmp qam_tmp qam;

%% 模数转换
fs_analog=512*fs; % 没办法,只能用极高的采样率来仿真模拟信号了

% 下面只是模数转换的一种概念形式,并非实现方法
t_ax_analog=0:1/fs_analog:(N_fft*fs_analog/fs-1)/fs_analog;
bb_analog=zeros(Ntx,length(t_ax_analog));

for i=1:Ntx
    bb_analog(i,:)=interp1(t_ax, bb(i,:), t_ax_analog, 'spline');
    figure('NumberTitle', 'off', 'Name', sprintf('Tx Chain %d',i));
    plot(t_ax_analog*1e6, real(bb_analog(i,:)));
    hold on;
    plot(t_ax_analog*1e6, imag(bb_analog(i,:)));
    hold off;
    axis([min(t_ax_analog)*1e6,max(t_ax_analog)*1e6,-1,1]);
    axis 'auto y';
    grid on;
    title('基带模拟信号');
    legend('实部','虚部','Location','SouthEast');
    xlabel('时间轴/\mus');
end

clear bb t_ax;

%% 正交调制到中频(200MHz中心频率)
fc_if=200e6; % 模拟中频频率

lo_if_I= cos(2*pi*fc_if*t_ax_analog);
lo_if_Q=-sin(2*pi*fc_if*t_ax_analog);

sig_if=real(bb_analog).*repmat(lo_if_I,Ntx,1)+imag(bb_analog).*repmat(lo_if_Q,Ntx,1);

clear bb_analog;

for i=1:Ntx
    figure('NumberTitle', 'off', 'Name', sprintf('Tx Chain %d',i));
    plot(t_ax_analog*1e6, real(sig_if(i,:)));
    axis([min(t_ax_analog)*1e6,max(t_ax_analog)*1e6,-1,1]);
    axis 'auto y';
    grid on;
    title('中频模拟信号');
    xlabel('时间轴/\mus');
end

%% 上变频到射频(2.4GHz)
