package com.mrwxb.demo3;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.Nullable;
import android.text.InputType;
import android.util.Log;
import android.view.View;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.gizwits.gizwifisdk.enumration.GizWifiErrorCode;
import com.qmuiteam.qmui.widget.dialog.QMUIDialog;
import com.qmuiteam.qmui.widget.dialog.QMUIDialogAction;
import com.wxb.mygizlib.ui.BaseDeviceControlActivity;

import java.util.concurrent.ConcurrentHashMap;

//子类
public class DeviceControlActivity extends BaseDeviceControlActivity implements View.OnClickListener {
    private  String DO1NAME="";
    private  String DO2NAME="";
    private  String DO3NAME="";
    private  String DO4NAME="";
    private  String DO5NAME="";
    private  String DO6NAME="";
    private  String DO7NAME="";
    private  String DO8NAME="";
    private  String DO9NAME="";
    private  String DI1NAME="";
    private  String DI2NAME="";
    private  String DI3NAME="";
    private  String DI4NAME="";
    private  String DI5NAME="";
    private  String DI6NAME="";
    private  String DI7NAME="";
    private  String DI8NAME="";
    private  String DI9NAME="";
    private Switch mDO1;
    private Switch mDO2;
    private Switch mDO3;
    private Switch mDO4;
    private Switch mDO5;
    private Switch mDO6;
    private TextView mAI1;
    private TextView mAI2;
    private Switch mDI1;
    private Switch mDI2;
    private Switch mDI3;
    private  static final String DO_1="DO1";
    private  static final String DO_2="DO2";
    private  static final String DO_3="DO3";
    private  static final String DO_4="DO4";
    private  static final String DO_5="DO5";
    private  static final String DO_6="DO6";
    private  static final String AI_1="AI1";
    private  static final String AI_2="AI2";
    private  static final String DI_1="DI1";
    private  static final String DI_2="DI2";
    private  static final String DI_3="DI3";

    // End Of Content View Elements
    private boolean  do1Switch=false;
    private boolean  do2Switch=false;
    private boolean  do3Switch=false;
    private boolean  do4Switch=false;
    private boolean  do5Switch=false;
    private boolean  do6Switch=false;
    private static double data_AI1;
    private static double data_AI2;
    private boolean  di1Switch=false;
    private boolean  di2Switch=false;
    private boolean  di3Switch=false;

    private void bindViews() {
        mDO1 = (Switch) findViewById(R.id.Do1);
        mDO2 = (Switch) findViewById(R.id.Do2);
        mDO3 = (Switch) findViewById(R.id.Do3);
        mDO4 = (Switch) findViewById(R.id.Do4);
        mDO5 = (Switch) findViewById(R.id.Do5);
        mDO6 = (Switch) findViewById(R.id.Do6);
        mAI1  = (TextView) findViewById(R.id.Ai1);
        mAI2  = (TextView) findViewById(R.id.Ai2);
        mDI1 = (Switch) findViewById(R.id.Di1);
        mDI2 = (Switch) findViewById(R.id.Di2);
        mDI3 = (Switch) findViewById(R.id.Di3);
        mDO1.setOnClickListener(this);
        mDO2.setOnClickListener(this);
        mDO3.setOnClickListener(this);
        mDO4.setOnClickListener(this);
        mDO5.setOnClickListener(this);
        mDO6.setOnClickListener(this);
    }
    private Handler mHandler =new Handler(){
        @Override
        public void dispatchMessage(Message msg) {
            super.dispatchMessage(msg);

            if(msg.what==108){
                updateUI();

            }
        }
    };

    private void updateUI() {
     mAI1.setText("温度"+data_AI1+"℃");
     mAI2.setText("湿度"+data_AI2+"%");
     mDO1.setChecked(do1Switch);
     mDO2.setChecked(do2Switch);
     mDO3.setChecked(do3Switch);
     mDO4.setChecked(do4Switch);
     mDO5.setChecked(do5Switch);
     mDO6.setChecked(do6Switch);
     mDI1.setChecked(di1Switch);
     mDI2.setChecked(di2Switch);
     mDI3.setChecked(di3Switch);

    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_device_control);
        initView();
    }

    private void initView() {
        mTopBar=findViewById(R.id.topBarCon);
        mTopBar.addLeftImageButton(com.wxb.mygizlib.R.mipmap.ic_back,com.wxb.mygizlib.R.id.topbar_left_icon).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });
        mTopBar.addRightTextButton("编辑节点名称",com.wxb.mygizlib.R.id.text).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                showReNamePointDialogClick();

            }
        });
        //判断名字改过没有，如果改过，就同步新的名字
        String tempTitle=mDevice.getAlias().isEmpty() ? mDevice.getProductName():mDevice.getAlias();
        mTopBar.setTitle(tempTitle);
        bindViews();
        pointNameInit();
    }
private  void pointNameInit(){
    SharedPreferences editor=getSharedPreferences("data",MODE_PRIVATE);
    //节点名字获取
    DO1NAME=editor.getString("DO1NAME","");
    DO2NAME=editor.getString("DO2NAME","");
    DO3NAME=editor.getString("DO3NAME","");
    DO4NAME=editor.getString("DO4NAME","");
    DO5NAME=editor.getString("DO5NAME","");
    DO6NAME=editor.getString("DO6NAME","");
    DI1NAME=editor.getString("DI1NAME","");
    DI2NAME=editor.getString("DI2NAME","");
    DI3NAME=editor.getString("DI3NAME","");
    mDO1.setText(DO1NAME);
    mDO2.setText(DO2NAME);
    mDO3.setText(DO3NAME);
    mDO4.setText(DO4NAME);
    mDO5.setText(DO5NAME);
    mDO6.setText(DO6NAME);
    mDI1.setText(DI1NAME);
    mDI2.setText(DI2NAME);
    mDI3.setText(DI3NAME);
}


    /******
     * 弹出节点名字修改选择对话框，选择节点
     */
    private void showReNamePointDialogClick() {
        //显示弹窗
        String[] items=new String[]{mDO1.getText().toString(),mDO2.getText().toString(),mDO3.getText().toString(),mDO4.getText().toString(),mDO5.getText().toString(),mDO6.getText().toString(),mDI1.getText().toString(),mDI2.getText().toString(),mDI3.getText().toString()};

        new QMUIDialog.MenuDialogBuilder(this).addItems(items, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                switch (i){
                    case 0:
                        showReNamePointDialog(mDO1);
                        break;
                    case 1:
                        showReNamePointDialog(mDO2);
                        break;
                    case 2:
                        showReNamePointDialog(mDO3);
                        break;
                    case 3:
                        showReNamePointDialog(mDO4);
                        break;
                    case 4:
                        showReNamePointDialog(mDO5);
                        break;
                    case 5:
                        showReNamePointDialog(mDO6);
                        break;
                    case 6:
                        showReNamePointDialog(mDI1);
                        break;
                    case 7:
                        showReNamePointDialog(mDI2);
                        break;
                     case 8:
                        showReNamePointDialog(mDI3);
                        break;

                }
                dialogInterface.dismiss();
            }
        }).show();

    }
    //重命名节点
    private void showReNamePointDialog(final  Switch switchId) {
        final QMUIDialog.EditTextDialogBuilder builder=new QMUIDialog.EditTextDialogBuilder(this);
        builder.setTitle("重命名")
                .setInputType(InputType.TYPE_CLASS_TEXT)
                .setPlaceholder("在此输入新名称")
                .addAction("取消", new QMUIDialogAction.ActionListener() {
                    @Override
                    public void onClick(QMUIDialog dialog, int index) {
                        dialog.dismiss();
                    }
                })
                .addAction("确认", new QMUIDialogAction.ActionListener() {
                    @Override
                    public void onClick(QMUIDialog dialog, int index) {
                        String newName= builder.getEditText().getText().toString().trim();
                        if(newName.isEmpty()){
                            Toast.makeText(DeviceControlActivity.this,"输入为空",Toast.LENGTH_SHORT).show();

                        }
                        else{
                            switchId.setText(newName);
                            SharedPreferences.Editor editor=getSharedPreferences("data",MODE_PRIVATE).edit();
                            switch (switchId.getId()){
                                case R.id.Do1:
                                    editor.putString("DO1NAME",newName);
                                    break;
                                case R.id.Do2:
                                    editor.putString("DO2NAME",newName);
                                    break;
                                case R.id.Do3:
                                    editor.putString("DO3NAME",newName);
                                    break;
                                case R.id.Do4:
                                    editor.putString("DO4NAME",newName);
                                    break;
                                case R.id.Do5:
                                    editor.putString("DO5NAME",newName);
                                    break;
                                case R.id.Do6:
                                    editor.putString("DO6NAME",newName);
                                    break;

                                case R.id.Di1:
                                    editor.putString("DI1NAME",newName);
                                    break;
                                case R.id.Di2:
                                    editor.putString("DI2NAME",newName);
                                    break;
                                case R.id.Di3:
                                    editor.putString("DI3NAME",newName);
                                    break;

                            }
                            editor.apply();

                        }
                        dialog.dismiss();

                    }
                })
                .show();
    }

    @Override
    protected void receiveCloudData(GizWifiErrorCode result, ConcurrentHashMap<String, Object> dataMap) {
        super.receiveCloudData(result, dataMap);
        Log.e("ZNJJ","子类界面"+dataMap);
        if(result==GizWifiErrorCode.GIZ_SDK_SUCCESS){
            if(dataMap!=null){

                parseReceiveData(dataMap);
            }

        }
    }
//解析数据
    private void parseReceiveData(ConcurrentHashMap<String, Object> dataMap) {
        if(dataMap.get("data")!=null){
            ConcurrentHashMap<String, Object> tempperDataMap= ( ConcurrentHashMap<String, Object>)dataMap.get("data");
                for(String dataKey:tempperDataMap.keySet()){
                    //温度
                    //通过云端定义的标识符来同步数据如LED1
                    if(dataKey.equals(DO_1)){
                        do1Switch= (boolean) tempperDataMap.get(DO_1);
                    }
                    if(dataKey.equals(DO_2)){
                        do2Switch= (boolean) tempperDataMap.get(DO_2);
                    }
                    if(dataKey.equals(DO_3)){
                        do3Switch= (boolean) tempperDataMap.get(DO_3);
                    }
                    if(dataKey.equals(DO_4)){
                        do4Switch= (boolean) tempperDataMap.get(DO_4);
                    }
                   if(dataKey.equals(DO_5)){
                       do5Switch= (boolean) tempperDataMap.get(DO_5);
                    }
                    if(dataKey.equals(DO_6)){
                        do6Switch= (boolean) tempperDataMap.get(DO_6);
                    }

                    if(dataKey.equals(AI_1)){
                        if (tempperDataMap.get(dataKey) instanceof Integer) {
                            data_AI1 = (Integer) tempperDataMap.get(dataKey);
                        } else {
                            data_AI1 = (Double) tempperDataMap.get(dataKey);
                        }
                    }
                    if(dataKey.equals(AI_2)){
                        if (tempperDataMap.get(dataKey) instanceof Integer) {
                            data_AI2 = (Integer) tempperDataMap.get(dataKey);
                        } else {
                            data_AI2 = (Double) tempperDataMap.get(dataKey);
                        }
                    }

                    if(dataKey.equals(DI_1)){
                        di1Switch= (boolean) tempperDataMap.get(DI_1);

                    }
                    if(dataKey.equals(DI_2)){
                        di2Switch= (boolean) tempperDataMap.get(DI_2);

                    }
                    if(dataKey.equals(DI_3)){
                        di3Switch= (boolean) tempperDataMap.get(DI_3);
                    }

                }
                mHandler.sendEmptyMessage(108);
        }

    }

    //按钮回调
    @Override
    public void onClick(View view) {
      if(view.getId()== R.id.Do1) {
          sendCommand(DO_1, mDO1.isChecked());
      }
      else if(view.getId()== R.id.Do2){
              sendCommand(DO_2,mDO2.isChecked());
      }
      else if(view.getId()== R.id.Do3){
          sendCommand(DO_3,mDO3.isChecked());
      }
      else if(view.getId()== R.id.Do4){
          sendCommand(DO_4,mDO4.isChecked());
      }
      else if(view.getId()== R.id.Do5){
          sendCommand(DO_5,mDO5.isChecked());
      }
      else if(view.getId()== R.id.Do6){
          sendCommand(DO_6,mDO6.isChecked());
      }
    }
}
