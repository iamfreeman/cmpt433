# NewsRepo

Not many industries are as dynamic and inviting as the technology industry. IT professional needs to constantly learn new knowledge and stay up-to-date with the trends to be on the edge of productivity. This application is a platform that grabs news and trending topics for technology enthusiasts and save their time needed to visit multiple news sites

## Deployment

In order to run the application, please ensure a vagrant has been setup.

```
$: vagrant up
Bringing machine 'default' up with 'virtualbox' provider...
==> default: Checking if box 'ubuntu/xenial64' is up to date...
==> default: A newer version of the box 'ubuntu/xenial64' for provider 'virtualbox' is
==> default: available! You currently have version '20180316.0.0'. The latest is version
==> default: '20180406.0.0'. Run `vagrant box update` to update.
==> default: Machine already provisioned. Run `vagrant provision` or use the `--provision`
==> default: flag to force provisioning. Provisioners marked to run always will still run.
==> default: Running provisioner: shell...
    default: Running: inline script
    default:
    default: > @ clean /home/vagrant/project/react-fullstack
    default: > babel-node tools/run clean
    default: [04:27:29] Starting 'clean'...
    default: [04:27:29] Finished 'clean' after 55 ms
    default:
    default: > @ start /home/vagrant/project/react-fullstack
    default: > babel-node tools/run start
    default: [20:21:19] Starting 'start'...
    default: [20:21:19] Starting 'clean'...
    default: [20:21:19] Finished 'clean' after 43 ms
    default: [20:21:19] Starting 'bound copy'...
    default: build/package.json
    default: [20:21:20] Finished 'bound copy' after 241 ms
    default: webpack built c68d3ed53bcb44b27be2 in 32958ms
    default: Child
    default:     Time: 32958ms
    default:                            Asset     Size  Chunks             Chunk Names
    default:     main.js?c68d3ed53bcb44b27be2  6.21 MB       0  [emitted]  main
    default: Child
    default:     Time: 30050ms
    default:             Asset    Size  Chunks             Chunk Names
    default:         server.js  381 kB       0  [emitted]  main
    default:     server.js.map  423 kB       0  [emitted]  main
    default: webpack: bundle is now VALID.
    default: [20:22:10] The server is running at http://localhost:3000/
    default: [Browsersync] Proxying: http://localhost:3000
    default: [Browsersync] Access URLs:
    default:  ----------------------------------
    default:        Local: http://localhost:3001
    default:     External: http://10.0.2.15:3001
    default:  ----------------------------------
    default:           UI: http://localhost:3002
    default:  UI External: http://10.0.2.15:3002
    default:  ----------------------------------
    default: [Browsersync] Watching files...
    default: [20:22:11] Finished 'start' after 51329 ms
    default: [Browsersync] Couldn't open browser (if you are using BrowserSync in a headless environment, you might want to set the open option to false)
    default: [Browsersync] Reloading Browsers... (buffered 3 events)
```

### Mongo Database

This application uses the [Mongo Lab](https://mlab.com) for the Mongo Database.

All data is stored in the database "news-repo", and it contains the following collections,
* news
* comments

### Access to Application

After running via vagrant, the application is accessible from ```http://localhost:3000```.

## Features

### Fetch News from Third-Party Sources

The server has an API path ```/fetch``` for scraping news articles from the following sites,
* Hacker News
* Techcrunch
* Techcrunch China
* Mashable
* The Next Web
* Wired
* Crypto Coins News

The fetched articles will be stored into the news collection.

### List Articles Getting Started

The server has an API path ```/news``` for returning all the stored news articles.
The data from backend server is displayed at ```http://localhost:3000```.

### Display Article Detail Information

The server has an API path ```/article/:id``` for returning all the information for an article.
The data from backend server is displayed at ```http://localhost:3000/article/:id```.


### Link to Original News Article

On the detail article page, there is an link icon to link to the original article.

### Link to Original News Site

On the detail article page, there is a tag to link to the original site where the aricle originates.

### Add Comment to News Article

The server has an API path ```/comment``` for adding a comment for an article.
On the detail article page, there is a form for adding new comments to an news article.

### List Article Comments

The server has an API path ```/comments/:id``` for returning all the comments for an article.
The data from backend server is displayed at ```http://localhost:3000/article/:id```.

### Support for Mobile Screens

The home page at ```http://localhost:3000``` is mobile-friendly and resizes reactively based on the screen resolutions.


## Reference
* Yeoman generator for React.js projects (https://www.npmjs.com/package/generator-react-fullstack)
* React Starter Kit (https://www.reactstarterkit.com/)
* News API (https://newsapi.org/)
* cors-anywhere (https://cors-anywhere.herokuapp.com/)
* Vagrant (https://www.vagrantup.com/)
* Comment System Example (https://github.com/ijason/NodeJS-Mongoose) (http://www.coding4developers.com/node-js/realtime-commenting-system-with-node-and-mongodb-realtime-commenting-on-post-using-node-js-and-socket-io/)
