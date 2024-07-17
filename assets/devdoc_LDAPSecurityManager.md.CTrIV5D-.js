import{_ as e,c as t,o as a,V as n}from"./chunks/framework.gBlNPWt_.js";const f=JSON.parse('{"title":"LDAP Security Manager Init","description":"","frontmatter":{},"headers":[],"relativePath":"devdoc/LDAPSecurityManager.md","filePath":"devdoc/LDAPSecurityManager.md","lastUpdated":1717686037000}'),o={name:"devdoc/LDAPSecurityManager.md"},i=n('<h1 id="ldap-security-manager-init" tabindex="-1">LDAP Security Manager Init <a class="header-anchor" href="#ldap-security-manager-init" aria-label="Permalink to &quot;LDAP Security Manager Init&quot;">​</a></h1><p>This document covers the main steps taken by the LDAP Security Manager during initialization. It is important to note that the LDAP Security Manager uses the LDAP protocol to access an Active Directory, AD. The AD is the store for users, groups, permissions, resources, and more. The term LDAP is generally overused to refer to both.</p><h2 id="ldap-instances" tabindex="-1">LDAP Instances <a class="header-anchor" href="#ldap-instances" aria-label="Permalink to &quot;LDAP Instances&quot;">​</a></h2><p>Each service and/or component using the LDAP security manager gets its own instance of the security manager. This includes a unique connection pool (see below). All operations described apply to each LDAP instance.</p><h2 id="initialization-steps" tabindex="-1">Initialization Steps <a class="header-anchor" href="#initialization-steps" aria-label="Permalink to &quot;Initialization Steps&quot;">​</a></h2><p>The following sections cover the main steps taken during initialization</p><h3 id="load-configuration" tabindex="-1">Load Configuration <a class="header-anchor" href="#load-configuration" aria-label="Permalink to &quot;Load Configuration&quot;">​</a></h3><p>The following items are loaded from the configuration:</p><h4 id="ad-hosts" tabindex="-1">AD Hosts <a class="header-anchor" href="#ad-hosts" aria-label="Permalink to &quot;AD Hosts&quot;">​</a></h4><p>The LDAP Security Manager supports using multiple ADs. The FQDN or IP address of each AD host is read from configuration data and stored internally. The source is a comma separated list stored in the <em>ldapAddress</em> config value. Each entry is added to a pool of ADs.</p><p><strong>Note that all ADs are expected to use the same credentials and have the same configuration</strong></p><h4 id="ad-credentials" tabindex="-1">AD Credentials <a class="header-anchor" href="#ad-credentials" aria-label="Permalink to &quot;AD Credentials&quot;">​</a></h4><p>AD credentials consist of a username and password. The LDAP security manager users these to perform all operations on behalf of users and components in the cluster. There are three potential sources for credentials.</p><ol><li>A Kubernetes secret. If the <em>ldapAdminSecretKey</em> config value is set, but <em>ldapAdminVaultId</em> is not (see 2) then the AD credentials are retrieved as Kubernetes secrets.</li><li>If both <em>ldapAdminSecretKey</em> and <em>ldapAdminVaultId</em> config values are present, the AD credentials are retrieved from the vault.</li><li>Hardcoded values from the <em>systemCommonName</em> and <em>systemPassword</em> config values stored in the environment.xml file.</li></ol><p>As stated above, when multiple ADs are in use, the configuration of each must be the same. This includes credentials.</p><h3 id="retrieve-server-information-from-the-ad" tabindex="-1">Retrieve Server Information from the AD <a class="header-anchor" href="#retrieve-server-information-from-the-ad" aria-label="Permalink to &quot;Retrieve Server Information from the AD&quot;">​</a></h3><p>During initialization, the security manager begins incrementing through the set of defined ADs until it is able to connect and retrieve information from an AD. Once retrieved, the information is used for all ADs (see statement above about all ADs being the same). The accessed AD is marked as the current AD and no other ADs are accessed during initialization.</p><p>The retrieved information is used to verify the AD type so the security manager adjusts for variations between types. Additionally, defined DNs may be adjusted to match AD type requirements.</p><h2 id="connections" tabindex="-1">Connections <a class="header-anchor" href="#connections" aria-label="Permalink to &quot;Connections&quot;">​</a></h2><p>The manager handles connections to an AD in order to perform required operations. It is possible that values such as permissions and resources may be cached to improve performance.</p><h3 id="connection-pool" tabindex="-1">Connection Pool <a class="header-anchor" href="#connection-pool" aria-label="Permalink to &quot;Connection Pool&quot;">​</a></h3><p>The LDAP security manager maintains a pool of LDAP connections. The pool is limited in size to <em>maxConnections</em> from the configuration. The connection pool starts empty. As connections are created, each is added to the pool until the max allowed is reached.</p><p>The following process is used when an LDAP connection is needed.</p><p>First, the connection pool is searched for a free connection. If found and valid, the connection is returned. A connection is considered free if no one is using it and valid if the AD can be accessed. If no valid free connections are found, a new uninitialized connection is created.</p><p>For a new connection, an attempt is made to connect to each AD starting with the current. See <strong>Handling AD Hosts</strong> below for how ADs are cycled when a connection fails. For each AD, as it cycles through, connection attempts are retried with a short delay between each. If unable to connect, the AD host is marked rejected and the next is attempted. Once a new connection has been established, if the max number of connections has not been reached yet, the connection is added to the pool.</p><p>It is important to note that if the pool has reached its max size, new connections will continue to be made, but are not saved in the pool. This allows the pool to maintain a steady working state, but allow for higher demand. Connections not saved to the pool are deleted once no longer in use.</p><h3 id="handling-ad-hosts" tabindex="-1">Handling AD Hosts <a class="header-anchor" href="#handling-ad-hosts" aria-label="Permalink to &quot;Handling AD Hosts&quot;">​</a></h3><p>The manager keeps a list of AD hosts and the index of the current host. The current host is used for all AD operations until there is a failure. At that time the manager marks the host as &quot;rejected&quot; and moves to the next host using a round-robin scheme.</p>',28),s=[i];function r(c,d,h,l,u,m){return a(),t("div",null,s)}const A=e(o,[["render",r]]);export{f as __pageData,A as default};
