package com.jtrzyna.coldenberg;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;


public class MainActivity extends Activity{

    public final static int REQUEST_ENABLE_BT = 3;
    public final static int _MSG_TEXT_BUTTON_CONNECT_L = 5;
    public final static int SUCCESS_CONNECT = 6;
    public final static int MESSAGE_READ = 7;
    public final static int ERROR = -1;
    public final static int TERMINATE = -2;
    private final static int _DUMMY = 0;

    //button
    ToggleButton buttonConnectL;

    //textView
    TextView textL;

    private BtManager btManagerL;

    private static final int _LEFT = 1;

    private static boolean DISCOVERY_STARTED_L = false;

    private static boolean foundBTTargetL = false;

    BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

    Handler mainHandler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            switch(msg.what){
                case SUCCESS_CONNECT:
                    if(msg.arg1 == _LEFT) {
                        buttonConnectL.setChecked(true);
                    }
                    break;
                case _MSG_TEXT_BUTTON_CONNECT_L:
                    buttonConnectL.setText(msg.obj.toString());
                    break;
                case MESSAGE_READ:
                    byte[] readBuf = (byte[]) msg.obj;

                    String readMessage = new String(readBuf, 0, msg.arg1);
                    int value = readBuf[1];//(int) readMessage.charAt(0);

                    textL.setText(Integer.toString( 0xFF & readBuf[1] ));
                    break;

                case ERROR:
                    Log.d("here comes", "THE ERROR");
                    switch(msg.arg1){
                        case TERMINATE:
                            Toast.makeText(getApplicationContext(), "No bluetooth detected", Toast.LENGTH_SHORT).show();
                            finish();
                            break;
                    }
                    //deactivateSystem();
                    break;
            }
        }
    };

    private final BroadcastReceiver mReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            if (BluetoothAdapter.ACTION_DISCOVERY_STARTED.equals(action)) {
                if(DISCOVERY_STARTED_L) {
                    mainHandler.obtainMessage(_MSG_TEXT_BUTTON_CONNECT_L, "searching...").sendToTarget();
                    foundBTTargetL = false;
                }
            }
            else if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                // Get the BluetoothDevice object from the Intent
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                // Add the name and address to an array adapter to show in a ListView

                if(device.getName().startsWith("HC")){//Unique device address
                    if(DISCOVERY_STARTED_L && (!foundBTTargetL) ){
                        mainHandler.obtainMessage(_MSG_TEXT_BUTTON_CONNECT_L, "connecting...").sendToTarget();
                        foundBTTargetL = true;
                        mBluetoothAdapter.cancelDiscovery();
                        btManagerL.connect(device);
                    }
                }
            }
            else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action)) {
                if((!foundBTTargetL) && DISCOVERY_STARTED_L){
                    buttonConnectL.setChecked(false);
                    Toast.makeText(getApplicationContext(), "Nie znaleziono urządzenia bluetooth", Toast.LENGTH_SHORT).show();
                }
                DISCOVERY_STARTED_L = false;
            }

            else if (BluetoothAdapter.ACTION_STATE_CHANGED.equals(action)) {
                final int state = intent.getIntExtra(BluetoothAdapter.EXTRA_STATE, BluetoothAdapter.ERROR);
                switch (state) {
                    case BluetoothAdapter.STATE_OFF:
                        buttonConnectL.setChecked(false);
                        Toast.makeText(getApplicationContext(), "Musisz włączyć bluetooth aby kontunuować", Toast.LENGTH_SHORT).show();
                        deactivate();
                        break;
                    case BluetoothAdapter.STATE_TURNING_OFF:
                        mainHandler.obtainMessage(_MSG_TEXT_BUTTON_CONNECT_L, "Turning off...").sendToTarget();
                        break;
                    case BluetoothAdapter.STATE_ON:
                        mainHandler.obtainMessage(_MSG_TEXT_BUTTON_CONNECT_L, "Connect").sendToTarget();
                        Log.d("state", "STATE ON");
                        if(DISCOVERY_STARTED_L){
                            Log.d("state", "STATE ON & DIS START == true");
                            mBluetoothAdapter.startDiscovery();
                        }
                        break;
                    case BluetoothAdapter.STATE_TURNING_ON:
                        Log.d("state", "TURNING ON");
                        mainHandler.obtainMessage(_MSG_TEXT_BUTTON_CONNECT_L, "Turning on...").sendToTarget();
                        break;
                }
            }
            else if (BluetoothDevice.ACTION_ACL_DISCONNECTED.equals(action)) {
                Toast.makeText(getApplicationContext(), "Utracono połączenie", Toast.LENGTH_SHORT).show();
                Log.d("state", "dev disconnected");
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initTextView();
        initButtons();
        initBt();
        registerIntentFilters();
    }

    void initTextView(){
        textL = (TextView) findViewById(R.id.text_L);
    }

    void initBt(){
        checkBluetoothAdapter();
        btManagerL = new BtManager(mainHandler, _LEFT); //handler to communicate, name to find
    }

    void initButtons(){
        buttonConnectL = (ToggleButton) findViewById(R.id.button_connectL);
    }

    private void registerIntentFilters(){
        IntentFilter filter = new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED);
        registerReceiver(mReceiver, filter);
        filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        registerReceiver(mReceiver, filter);
        filter = new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        registerReceiver(mReceiver, filter);
        filter = new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        registerReceiver(mReceiver, filter);
    }

    private void checkBluetoothAdapter(){
        if (mBluetoothAdapter == null) {
            Toast.makeText(getApplicationContext(), "No bluetooth detected", Toast.LENGTH_SHORT).show();
            finish();
            // Device does not support Bluetooth
        }
    }

    private void deactivate(){

        if(DISCOVERY_STARTED_L){
            mBluetoothAdapter.cancelDiscovery();
        }
        disconnect();
    }

    private void disconnect(){

        DISCOVERY_STARTED_L = false;
        foundBTTargetL = false;
        btManagerL.disconnect();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public void onButtonConnectLClicked(View view) {
        Log.d("Method", "onConnectLClicked");
        boolean on = buttonConnectL.isChecked();
        if(on){
            DISCOVERY_STARTED_L = true;
            if (!mBluetoothAdapter.isEnabled()) {
                Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
            }
            else{
                mBluetoothAdapter.startDiscovery();
            }
        }
        else{
            disconnect();
        }
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == REQUEST_ENABLE_BT) {
            if (resultCode == RESULT_CANCELED) {
                buttonConnectL.setChecked(false);
                Toast.makeText(getApplicationContext(), "Wystąpił błąd przy włączaniu bluetootha", Toast.LENGTH_SHORT).show();
            }
            /*
            else if(resultCode == RESULT_OK){
                //if ok - BroadcastReceiver can handle it
            }*/
        }
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        // Unregister broadcast listeners
        unregisterReceiver(mReceiver);
        deactivate();
    }
}
