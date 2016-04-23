package com.spaceapps.asteroidmining3;


import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.Reader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;


/**
 * Created by Luciano on 22/04/2016.
 */

public class MainActivity extends AppCompatActivity {

    private Button btnExecute, btnCar, btnCrane, btnBluetooth;
    private EditText edtIp, edtPort, edtManualCommand;
    private Spinner spinCommands;

    List<Integer> listCommands = new ArrayList<Integer>();

    String address = null;
    private ProgressDialog progress;

    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private ConnectBT conexion;

    private static final String TAG = MainActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Intent newint = getIntent();
        address = newint.getStringExtra(DeviceList.EXTRA_ADDRESS); //recivimos la mac address obtenida en la actividad anterior

/*

        AlertDialog alertDialog = new AlertDialog.Builder(MainActivity.this).create();
        alertDialog.setTitle("Alert");
        alertDialog.setMessage("Alert message to be shown");
        alertDialog.setButton(AlertDialog.BUTTON_NEUTRAL, "OK",
                new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                });
        alertDialog.show();*/



        btnExecute = (Button) findViewById(R.id.btnExecute);
        btnCar = (Button) findViewById(R.id.btnCar);
        btnCrane = (Button) findViewById(R.id.btnCrane);
        btnBluetooth = (Button) findViewById(R.id.btnBluetooth);

        edtIp = (EditText) findViewById(R.id.edtIp);
        edtPort = (EditText) findViewById(R.id.edtPort);
        edtManualCommand = (EditText) findViewById(R.id.edtManualCommand);
        spinCommands = (Spinner) findViewById(R.id.spinCommands);


        SharedPreferences myPrefs = getSharedPreferences("Preferences", Context.MODE_PRIVATE);
        edtIp.setText(myPrefs.getString("ip", ""));
        edtPort.setText(myPrefs.getString("port", ""));


        for (Integer i=33; i<=233;i++){
            if (i==34 || i==39 || i==92)
                continue;

            listCommands.add(i);
        }
        ArrayAdapter<Integer> adapter = new ArrayAdapter<Integer>(this,
                android.R.layout.simple_spinner_item, listCommands);
        spinCommands.setAdapter(adapter);


        btnExecute.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                String command;
                if (edtManualCommand.length()>0)
                    command = edtManualCommand.getText().toString().trim();
                else
                    command = spinCommands.getSelectedItem().toString().trim();

                String url = "http://" + edtIp.getText().toString().trim() +":" + edtPort.getText().toString().trim() +"/?command=" + command;

                //Show url
                Toast.makeText(getApplicationContext(), url, Toast.LENGTH_LONG).show();

                //Save ip in preferences of the application
                SharedPreferences myPrefs = getSharedPreferences("Preferences", Context.MODE_PRIVATE);

                SharedPreferences.Editor editor = myPrefs.edit();
                editor.putString("ip", edtIp.getText().toString().trim());
                editor.putString("port", edtPort.getText().toString().trim());
                editor.commit();

                //Init execute request
                new DownloadTask().execute(url);


            }
        });
        btnCar.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this, ControlCarActivity.class));
            }
        });
        btnCrane.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this, ControlCraneActivity.class));
            }
        });
        btnBluetooth.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                conexion = new ConnectBT();//.execute(); //Call the class to connect
                conexion.execute();


                try
                {
                    btSocket.getOutputStream().write("TO".toString().getBytes());
                }
                catch (IOException e)
                {
                    msg("Error");
                }

            }
        });


    }


    private class DownloadTask extends AsyncTask<String, Void, String> {

        @Override
        protected String doInBackground(String... params) {
            //do your request in here so that you don't interrupt the UI thread
            try {
                return downloadContent(params[0]);
            } catch (IOException e) {
                return "Unable to retrieve data. URL or port invalid.";
            }
        }

        @Override
        protected void onPostExecute(String result) {
            //Here you are done with the task
            Toast.makeText(MainActivity.this, result, Toast.LENGTH_LONG).show();
        }
    }

    private String downloadContent(String myurl) throws IOException {
        InputStream is = null;
        int length = 500;

        try {
            URL url = new URL(myurl);
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setReadTimeout(10000 /* milliseconds */);
            conn.setConnectTimeout(15000 /* milliseconds */);
            conn.setRequestMethod("GET");
            conn.setDoInput(true);
            conn.connect();
            int response = conn.getResponseCode();
            Log.d(TAG, "The response is: " + response);
            is = conn.getInputStream();

            // Convert the InputStream into a string
            String contentAsString = convertInputStreamToString(is, length);
            return contentAsString;
        } finally {
            if (is != null) {
                is.close();
            }
        }
    }

    public String convertInputStreamToString(InputStream stream, int length) throws IOException, UnsupportedEncodingException {
        Reader reader = null;
        reader = new InputStreamReader(stream, "UTF-8");
        char[] buffer = new char[length];
        reader.read(buffer);
        return new String(buffer);
    }



    //Bluetooth
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();

        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private class ConnectBT extends AsyncTask<Void, Void, Void>  // UI thread
    {
        private boolean ConnectSuccess = true;

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(MainActivity.this, "Connecting...", "Please wait!!!");
        }



        @Override
        protected Void doInBackground(Void... devices)
        {

            try
            {
                if (btSocket == null || !isBtConnected)
                {

                    myBluetooth = BluetoothAdapter.getDefaultAdapter();
                    BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);//conectamos al dispositivo y chequeamos si esta disponible
                    btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    btSocket.connect();
                }
            }
            catch (IOException e)
            {
                ConnectSuccess = false;
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void result)
        {
            super.onPostExecute(result);

            if (!ConnectSuccess)
            {
                msg("Conexión Fallida");
                finish();
            }
            else
            {
                msg("Conectado");
                isBtConnected = true;
            }
            progress.dismiss();



        }
    }




    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
    }
}
