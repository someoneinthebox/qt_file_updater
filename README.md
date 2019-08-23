# qt_file_updater
A simple plug-in module for Qt to check updates for your soft and for update as a result

# Plug-in purpose
A plugin encapsulates into your Qt project and then you can check available update for your software by calling its controller. All you need is create protocol JSON-file with update data.

# Quick start
Just include **.pri** file into your project and somewhere in your code call:

```c++
Controller_FU c(your_int_version_variable, "https://your_site.com/path_to_update_file");
c.exec();
```

# Protocol

### Example:

```json
{
    "programName": "Your_Software_Name",
    "actualVersion": "3.7.6.6",
    "versions":
    {
         "3766":
         {
              "desc": "Some update info",
              "updateFiles":
              {
                 "app.exe": "https://cloud.your_site.com/index.php/s/K2Tbejh54fvsEVdJI/download",
                 "test.ini": "https://cloud.your_site.com/index.php/s/K2Tbehgj7fs675fj/download"
              }
         },
         "3765":
         {
              "desc": "
              <p>3.7.6.5</p>
              <ul>
                <li>Description can be html-like.</li>
              </ul>
              ",
              "updateFiles":
              {
                 "need.dll": "https://cloud.your_site.com/index.php/s/K2Tbejh54fvsEVdJI/download",
                 "test.sh": "https://cloud.your_site.com/index.php/s/K2Tbejhf88vsEVdJI/download"
              }
         },
         "3764":
         {
              "desc": "Another description",
              "updateFiles":
              {
                 "app.exe": "https://cloud.your_site.com/index.php/s/K2Tbejh54fvsEVdJI/download"
              }
         }
    }
}
```

### Description:


1. **programName** - string, software name;
2. **actualVersion** - string, your actual user-like software version;
3. **versions** - json object with data:
   - **N** - string, where N is software numeric version with data:
     - **desc** - string, update description;
     - **updateFiles** - json object with key - filename and value - url to file
